#include "manager/middleware_manager.hpp"

#include <windows.h>

#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/thread.hpp>

#include "manager/signal_manager.hpp"

#include "macro_utility.h"

using namespace godot;
using namespace framework;

#define TAG "[MiddlewareManager]"

MiddlewareManager *MiddlewareManager::p_instance = nullptr;

MiddlewareManager *MiddlewareManager::get_instance() {
    RETURN_INSTANCE()
}

void MiddlewareManager::_bind_methods() {}

MiddlewareManager::MiddlewareManager() {
    INIT_INSTANCE()
    print_verbose(TAG"Created.");
}

MiddlewareManager::~MiddlewareManager() {
    p_instance = nullptr;
}

void MiddlewareManager::_ready() {
    // Check resource
    GET_VARIANT_PROPERTY(calibration_path, STRING)
    GET_VARIANT_PROPERTY(fusion_path, STRING)

    // Get data point

    // Connect framework signal

    print_verbose(TAG"Ready.");
}

void MiddlewareManager::_exit_tree() {
    // Disconnect framework signal

    print_verbose(TAG"Exit tree.");
}

String MiddlewareManager::get_process_executable_file_path(EMiddleware object) {
    String path = OS::get_singleton()->get_executable_path().get_base_dir();
    if (!path.ends_with("/")) {
        path = path + "/";
    }

    switch (object) {
        case EMiddleware::CALIBRATION:
            path = path + m_calibration_path;
            break;
        
        case EMiddleware::FUSION:
            path = path + m_fusion_path;
            break;

        default:;
    }

    if (!FileAccess::file_exists(path)) {
        print_error(vformat(TAG"%s does not exist!", path));
        return String("");
    }

    return path;
}

Error MiddlewareManager::create_calibration_shared_data() {
    HANDLE file_mapping_handle = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        m_calibration_process_handle.shared_data_size,
        reinterpret_cast<LPCSTR>(m_calibration_process_handle.shared_data_name.utf8().get_data())
    );

    if (file_mapping_handle == INVALID_HANDLE_VALUE) {
        print_error(vformat(TAG"Create %s file mapping failed!", m_calibration_process_handle.shared_data_name));
        return Error::FAILED;
    }

    LPVOID p_shared_data_buffer = MapViewOfFile(
        file_mapping_handle,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        m_calibration_process_handle.shared_data_size
    );

    if (p_shared_data_buffer == nullptr) {
        print_error(vformat(TAG"Point of %s is null!", m_calibration_process_handle.shared_data_name));
        CloseHandle(file_mapping_handle);
        return Error::FAILED;
    }

    m_calibration_process_handle.p_file_mapping_handle = file_mapping_handle;
    m_calibration_process_handle.p_shared_data_buffer = p_shared_data_buffer;

    print_verbose(vformat(
        TAG"Create shared data %s with size %lu success.",
        m_calibration_process_handle.shared_data_name,
        m_calibration_process_handle.shared_data_size
    ));

    middleware::CalibrationProcessCommand *p_process_command =
            reinterpret_cast<middleware::CalibrationProcessCommand *>(m_calibration_process_handle.p_shared_data_buffer);

    p_process_command[0].id = 0;
    p_process_command[0].type = 0;
    p_process_command[0].command = 0;

    p_process_command[1].id = 0;
    p_process_command[1].type = 0;
    p_process_command[1].command = 0;

    m_calibration_process_handle.last_sub_process_command_id = 0;
    m_calibration_process_handle.wait_response_flag = false;
    m_calibration_process_handle.wait_response_counter = 0;

    return Error::OK;
}

void MiddlewareManager::release_calibration_shared_data() {
    if (m_calibration_process_handle.p_shared_data_buffer != nullptr) {
        UnmapViewOfFile(m_calibration_process_handle.p_shared_data_buffer);
        m_calibration_process_handle.p_shared_data_buffer = nullptr;
        print_verbose(vformat(TAG"Release shared data %s success.", m_calibration_process_handle.shared_data_name));
    }

    if (m_calibration_process_handle.p_file_mapping_handle != nullptr) {
        CloseHandle(m_calibration_process_handle.p_file_mapping_handle);
        m_calibration_process_handle.p_file_mapping_handle = nullptr;
        print_verbose(vformat(TAG"Release %s file mapping success.", m_calibration_process_handle.shared_data_name));
    }
}

void MiddlewareManager::send_calibration_process_command(uint8_t type, uint8_t command) {
    if (m_calibration_process_handle.p_shared_data_buffer == nullptr) {
        return;
    }

    middleware::CalibrationProcessCommand *p_process_command =
            reinterpret_cast<middleware::CalibrationProcessCommand *>(m_calibration_process_handle.p_shared_data_buffer);

    p_process_command[0].id++;
    p_process_command[0].type = (uint8_t)type;
    p_process_command[0].command = command;

    m_calibration_process_handle.wait_response_flag = true;
}

void MiddlewareManager::send_calibration_response() {
    if (m_calibration_process_handle.p_shared_data_buffer == nullptr) {
        return;
    }

    middleware::CalibrationProcessCommand *p_process_command =
            reinterpret_cast<middleware::CalibrationProcessCommand *>(m_calibration_process_handle.p_shared_data_buffer);

    p_process_command[0].id++;
    p_process_command[0].type = (uint8_t)middleware::EProcessCommandType::RESPONSE;
    p_process_command[0].command = 0;
}

void MiddlewareManager::listen_calibration_sub_process_command() {
    if (m_calibration_process_handle.p_shared_data_buffer == nullptr) {
        return;
    }

    if (m_calibration_process_handle.wait_response_flag) {
        if (m_calibration_process_handle.wait_response_counter > (500U / 16U)) {
            SignalManager::get_instance()->signal_emit_deferred(ESignal::CALIBRATION_NONE_RESPONSE);
            m_calibration_process_handle.wait_response_flag = false;
            m_calibration_process_handle.wait_response_counter = 0;
            return;
        } else {
            m_calibration_process_handle.wait_response_counter++;
        }
    }

    middleware::CalibrationProcessCommand *p_process_command =
            reinterpret_cast<middleware::CalibrationProcessCommand *>(m_calibration_process_handle.p_shared_data_buffer);

    if (m_calibration_process_handle.last_sub_process_command_id == p_process_command[1].id) {
        return;
    }

    print_verbose(vformat(TAG"Sub process command: %d-%d.", p_process_command[1].type, p_process_command[1].command));

    m_calibration_process_handle.last_sub_process_command_id = p_process_command[1].id;

    if (p_process_command[1].command == (uint8_t)middleware::EProcessCommandType::RESPONSE) {
        m_calibration_process_handle.wait_response_flag = false;
        m_calibration_process_handle.wait_response_counter = 0;
        return;
    }

    calibration_sub_process_command_parser();
}

void MiddlewareManager::calibration_sub_process_command_parser() {

}

void MiddlewareManager::calibration_monitor_task() {
    print_verbose(TAG"Calibration monitor task begin.");
    DWORD process_exit_code;

    middleware::CalibrationSharedData *p_calibration_shared_data = 
            reinterpret_cast<middleware::CalibrationSharedData *>(m_calibration_process_handle.p_shared_data_buffer);
    
    if (p_calibration_shared_data == nullptr) {
        goto task_end;
    }

    while(1) {
        if (
            GetExitCodeProcess(m_calibration_process_handle.p_process_handle, &process_exit_code) &&
            process_exit_code != STILL_ACTIVE
        ) {
            print_verbose(vformat(TAG"Calibration process exited with code: %d.", static_cast<uint32_t>(process_exit_code)));
            break;
        }

        if (m_calibration_process_handle.is_running) {
            listen_calibration_sub_process_command();
        } else {
            if (m_calibration_process_handle.exit_wait_counter > (500U / 16U)) {
                print_verbose(vformat(TAG"Calibration process exited with timeout."));
                TerminateProcess(m_calibration_process_handle.p_process_handle, 0);
                WaitForSingleObject(m_calibration_process_handle.p_process_handle, 1000);
                continue;
            } else {
                m_calibration_process_handle.exit_wait_counter++;
            }
        }

        OS::get_singleton()->delay_msec(16);
    }

    CloseHandle(m_calibration_process_handle.p_process_handle);
    m_calibration_process_handle.p_process_handle = nullptr;
    m_calibration_process_handle.exit_wait_counter = 0;

    if (m_calibration_process_handle.is_running) {
        m_calibration_process_handle.is_running = false;
    } else {
        release_calibration_shared_data();
    }

task_end:
    print_verbose(TAG"Calibration monitor task end.");
}

Error MiddlewareManager::run_calibration() {
    String path;

    STARTUPINFOA s_info = {0};
    s_info.cb = sizeof(s_info);
    PROCESS_INFORMATION p_info = {0};

    if (!m_enabled) {
        goto error_0;
    }

    path = get_process_executable_file_path(EMiddleware::CALIBRATION);
    if (path.is_empty()) {
        goto error_0;
    }

    if (create_calibration_shared_data() != Error::OK) {
        goto error_0;
    }

    if (!CreateProcessA(
        reinterpret_cast<LPCSTR>(path.utf8().get_data()),
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &s_info,
        &p_info
    )) {
        print_error(vformat(TAG"Run %s failed!", path));
        goto error_1;
    }

    m_calibration_process_handle.p_process_handle = p_info.hProcess;
    CloseHandle(p_info.hThread);

    m_calibration_process_handle.is_running = true;

    if (!m_calibration_process_handle.monitor_thread->start(callable_mp(this, &MiddlewareManager::calibration_monitor_task)) == Error::OK) {
        print_error(vformat(TAG"Start the monitor thread of %s failed!", path));
        goto error_2;
    }

    return Error::OK;

error_2:
    m_calibration_process_handle.is_running = false;
    TerminateProcess(m_calibration_process_handle.p_process_handle, 0);
    CloseHandle(m_calibration_process_handle.p_process_handle);
    m_calibration_process_handle.p_process_handle = nullptr;
error_1:
    release_calibration_shared_data();
error_0:
    return Error::FAILED;
}

void MiddlewareManager::init() {
    m_calibration_process_handle.monitor_thread.instantiate();
    m_calibration_process_handle.shared_data_name = CALIBRATION_SHARED_DATA_NAME;
    m_calibration_process_handle.shared_data_size = sizeof(middleware::CalibrationSharedData);
    m_calibration_process_handle.last_sub_process_command_id = 0;
    m_calibration_process_handle.is_running = false;
    m_calibration_process_handle.exit_wait_counter = 0;

    ENABLE_FLAG()

    print_verbose(TAG"Init.");
}

void MiddlewareManager::deinit() {
    DISABLE_FLAG()

    release(EMiddleware::CALIBRATION);

    if (m_calibration_process_handle.monitor_thread->is_started()) {
        m_calibration_process_handle.monitor_thread->wait_to_finish();
    }

    release(EMiddleware::FUSION);

    print_verbose(TAG"Deinit.");
}

Error MiddlewareManager::run(EMiddleware object) {
    if (!m_enabled) {
        return Error::FAILED;
    }

    switch (object) {
        case EMiddleware::CALIBRATION:
            return run_calibration();
            break;
        
        case EMiddleware::FUSION:
            return Error::FAILED;
            break;

        default:
            return Error::FAILED;
    }
}

void MiddlewareManager::release(EMiddleware object) {
    if (!m_enabled) {
        return;
    }

    switch (object) {
        case EMiddleware::CALIBRATION:
            if (m_calibration_process_handle.is_running) {
                send_calibration_process_command((uint8_t)middleware::EProcessCommandType::EXIT, 1);
                m_calibration_process_handle.is_running = false;
            } else {
                release_calibration_shared_data();
            }

            break;
        
        case EMiddleware::FUSION:

            break;

        default:;
    }
}

bool MiddlewareManager::is_running(EMiddleware object) {
    if (!m_enabled) {
        return false;
    }

    switch (object) {
        case EMiddleware::CALIBRATION:
            return m_calibration_process_handle.is_running;
        
        case EMiddleware::FUSION:
            return false;

        default:
            return false;
    }
}

const middleware::CalibrationMonitorData *MiddlewareManager::get_calibration_monitor_data() {
    if (!m_enabled || m_calibration_process_handle.p_shared_data_buffer == nullptr) {
        return nullptr;
    }

    return reinterpret_cast<const middleware::CalibrationMonitorData *>(
        &reinterpret_cast<const middleware::CalibrationSharedData *>(m_calibration_process_handle.p_shared_data_buffer)->monitor_data
    );
}

const middleware::CalibrationSamplingData *MiddlewareManager::get_calibration_sampling_data() {
    if (!m_enabled || m_calibration_process_handle.p_shared_data_buffer == nullptr) {
        return nullptr;
    }

    return reinterpret_cast<const middleware::CalibrationSamplingData *>(
        &reinterpret_cast<const middleware::CalibrationSharedData *>(m_calibration_process_handle.p_shared_data_buffer)->sampling_data
    );
}

const middleware::CalibrationResultData *MiddlewareManager::get_calibration_result_data() {
    if (!m_enabled || m_calibration_process_handle.p_shared_data_buffer == nullptr) {
        return nullptr;
    }

    return reinterpret_cast<const middleware::CalibrationResultData *>(
        &reinterpret_cast<const middleware::CalibrationSharedData *>(m_calibration_process_handle.p_shared_data_buffer)->result_data
    );
}
