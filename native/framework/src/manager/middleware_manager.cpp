#include "manager/middleware_manager.hpp"

#include <windows.h>

#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/thread.hpp>

#include "manager/signal_manager.hpp"

#include "macro_utility.h"

#include "calibration_shared_data.h"

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
    GET_VARIANT_PROPERTY(calibration_path, m_calibration_path, STRING)
    GET_VARIANT_PROPERTY(fusion_path, m_fusion_path, STRING)

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

Error MiddlewareManager::create_shared_data(ProcessHandle *p_process_handle) {
    HANDLE map_file_handle = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        p_process_handle->shared_data_size,
        reinterpret_cast<LPCSTR>(p_process_handle->shared_data_name.utf8().get_data())
    );

    if (map_file_handle == INVALID_HANDLE_VALUE) {
        print_error(vformat(TAG"Create %s file mapping failed!", p_process_handle->shared_data_name));
        return Error::FAILED;
    }

    LPVOID p_shared_data_buffer = MapViewOfFile(
        map_file_handle,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        p_process_handle->shared_data_size
    );

    if (p_shared_data_buffer == nullptr) {
        print_error(vformat(TAG"Point of %s is null!", p_process_handle->shared_data_name));
        CloseHandle(map_file_handle);
        return Error::FAILED;
    }

    p_process_handle->p_map_file_handle = map_file_handle;
    p_process_handle->p_shared_data_buffer = p_shared_data_buffer;

    print_verbose(vformat(
        TAG"Create shared data %s with size %lu success.",
        p_process_handle->shared_data_name,
        p_process_handle->shared_data_size
    ));

    return Error::OK;
}

void MiddlewareManager::release_shared_data(ProcessHandle *p_process_handle) {
    if (p_process_handle->p_shared_data_buffer != nullptr) {
        UnmapViewOfFile(p_process_handle->p_shared_data_buffer);
        p_process_handle->p_shared_data_buffer = nullptr;
    }

    if (p_process_handle->p_map_file_handle != nullptr) {
        CloseHandle(p_process_handle->p_map_file_handle);
        p_process_handle->p_map_file_handle = nullptr;
    }
}

void MiddlewareManager::init_shared_data_process_command(ProcessHandle *p_process_handle) {
    if (p_process_handle->p_shared_data_buffer == nullptr) {
        return;
    }

    middleware::ProcessCommand *p_process_command =
            reinterpret_cast<middleware::ProcessCommand *>(p_process_handle->p_shared_data_buffer);

    p_process_command[0].id = 0;
    p_process_command[0].type = 0;
    p_process_command[0].command = 0;

    p_process_command[1].id = 0;
    p_process_command[1].type = 0;
    p_process_command[1].command = 0;

    p_process_handle->last_sub_process_command_id = 0;
    p_process_handle->wait_response_flag = false;
    p_process_handle->wait_response_counter = 0;
}

void MiddlewareManager::send_shared_data_process_command(ProcessHandle *p_process_handle, uint8_t type, uint8_t command) {
    if (p_process_handle->p_shared_data_buffer == nullptr) {
        return;
    }

    middleware::ProcessCommand *p_process_command =
            reinterpret_cast<middleware::ProcessCommand *>(p_process_handle->p_shared_data_buffer);

    p_process_command[0].id++;
    p_process_command[0].type = (uint8_t)type;
    p_process_command[0].command = command;

    p_process_handle->wait_response_flag = true;
}

void MiddlewareManager::send_response(ProcessHandle *p_process_handle) {
    if (p_process_handle->p_shared_data_buffer == nullptr) {
        return;
    }

    middleware::ProcessCommand *p_process_command =
            reinterpret_cast<middleware::ProcessCommand *>(p_process_handle->p_shared_data_buffer);

    p_process_command[0].id++;
    p_process_command[0].type = (uint8_t)middleware::EProcessCommandType::RESPONSE;
    p_process_command[0].command = 0;
}

void MiddlewareManager::listen_sub_process_command(ProcessHandle *p_process_handle) {
    if (p_process_handle->p_shared_data_buffer == nullptr) {
        return;
    }

    if (p_process_handle->wait_response_flag) {
        if (p_process_handle->wait_response_counter > (500U / 16U)) {
            SignalManager::get_instance()->signal_emit_deferred(ESignal::CALIBRATION_NONE_RESPONSE);
            p_process_handle->wait_response_flag = false;
            p_process_handle->wait_response_counter = 0;
            return;
        } else {
            p_process_handle->wait_response_counter++;
        }
    }

    middleware::ProcessCommand *p_process_command =
            reinterpret_cast<middleware::ProcessCommand *>(p_process_handle->p_shared_data_buffer);

    if (p_process_handle->last_sub_process_command_id == p_process_command[1].id) {
        return;
    }

    print_verbose(vformat(TAG"Sub process command: %d-%d.", p_process_command[1].type, p_process_command[1].command));

    p_process_handle->last_sub_process_command_id = p_process_command[1].id;

    if (p_process_command[1].command == (uint8_t)middleware::EProcessCommandType::RESPONSE) {
        p_process_handle->wait_response_flag = false;
        p_process_handle->wait_response_counter = 0;
        return;
    }

    switch (p_process_handle->type) {
        case EMiddleware::CALIBRATION:
            calibration_sub_process_command_parser();
            break;
        
        case EMiddleware::FUSION:
            fusion_sub_process_command_parser();
            break;

        default:;
    }
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
            listen_sub_process_command(&m_calibration_process_handle);
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

    release_shared_data(&m_calibration_process_handle);

task_end:
    print_verbose(TAG"Calibration monitor task end.");
}

void MiddlewareManager::fusion_sub_process_command_parser() {

}

void MiddlewareManager::fusion_monitor_task() {
    print_verbose(TAG"Fusion monitor task begin.");

    print_verbose(TAG"Fusion monitor task end.");
}

void MiddlewareManager::init() {
    m_calibration_process_handle.type = EMiddleware::CALIBRATION;
    m_calibration_process_handle.monitor_thread.instantiate();
    m_calibration_process_handle.shared_data_name = CALIBRATION_SHARED_DATA_NAME;
    m_calibration_process_handle.shared_data_size = sizeof(middleware::CalibrationSharedData);
    m_calibration_process_handle.last_sub_process_command_id = 0;
    m_calibration_process_handle.is_running = false;
    m_calibration_process_handle.exit_wait_counter = 0;


    m_fusion_process_handle.type = EMiddleware::FUSION;
    m_fusion_process_handle.monitor_thread.instantiate();
    // m_fusion_process_handle.shared_data_name = FUSION_SHARED_DATA_NAME;
    // m_fusion_process_handle.shared_data_size = sizeof(middleware::FusionSharedData);
    m_fusion_process_handle.last_sub_process_command_id = 0;
    m_fusion_process_handle.is_running = false;
    m_fusion_process_handle.exit_wait_counter = 0;

    ENABLE_FLAG()

    print_verbose(TAG"Init.");
}

void MiddlewareManager::deinit() {
    DISABLE_FLAG()

    if (m_calibration_process_handle.is_running) {
        stop(EMiddleware::CALIBRATION);

        if (m_calibration_process_handle.monitor_thread->is_started()) {
            m_calibration_process_handle.monitor_thread->wait_to_finish();
        }
    }

    if (m_fusion_process_handle.is_running) {
        stop(EMiddleware::FUSION);

        if (m_fusion_process_handle.monitor_thread->is_started()) {
            m_fusion_process_handle.monitor_thread->wait_to_finish();
        }
    }

    print_verbose(TAG"Deinit.");
}

Error MiddlewareManager::run(EMiddleware object) {
    ProcessHandle *p_process_handle = nullptr;
    Callable monitor_task_callable;
    String path;

    STARTUPINFOA s_info = {0};
    s_info.cb = sizeof(s_info);
    PROCESS_INFORMATION p_info = {0};

    if (!m_enabled) {
        goto error_0;
    }

    switch (object) {
        case EMiddleware::CALIBRATION:
            p_process_handle = &m_calibration_process_handle;
            monitor_task_callable = callable_mp(this, &MiddlewareManager::calibration_monitor_task);
            break;
        
        case EMiddleware::FUSION:
            p_process_handle = &m_fusion_process_handle;
            monitor_task_callable = callable_mp(this, &MiddlewareManager::fusion_monitor_task);
            break;

        default:
            goto error_0;
    }

    path = get_process_executable_file_path(object);
    if (path.is_empty()) {
        goto error_0;
    }

    if (create_shared_data(p_process_handle) != Error::OK) {
        goto error_0;
    }

    init_shared_data_process_command(p_process_handle);

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

    p_process_handle->p_process_handle = p_info.hProcess;
    CloseHandle(p_info.hThread);

    m_calibration_process_handle.is_running = true;

    if (!p_process_handle->monitor_thread->start(monitor_task_callable) == Error::OK) {
        print_error(vformat(TAG"Start the monitor thread of %s failed!", path));
        goto error_2;
    }

    return Error::OK;

error_2:
    m_calibration_process_handle.is_running = false;
    TerminateProcess(p_process_handle->p_process_handle, 0);
    CloseHandle(p_process_handle->p_process_handle);
    p_process_handle->p_process_handle = nullptr;
error_1:
    release_shared_data(p_process_handle);
error_0:
    return Error::FAILED;
}

void MiddlewareManager::stop(EMiddleware object) {
    if (!m_enabled) {
        return;
    }

    ProcessHandle *p_process_handle = nullptr;

    switch (object) {
        case EMiddleware::CALIBRATION:
            p_process_handle = &m_calibration_process_handle;
            break;
        
        case EMiddleware::FUSION:
            p_process_handle = &m_fusion_process_handle;
            break;

        default:
            return;
    }

    if (!p_process_handle->is_running) {
        return;
    }

    send_shared_data_process_command(p_process_handle, (uint8_t)middleware::EProcessCommandType::EXIT, 1);
    p_process_handle->is_running = false;
}

bool MiddlewareManager::is_running(EMiddleware object) {
    if (!m_enabled) {
        return false;
    }

    switch (object) {
        case EMiddleware::CALIBRATION:
            return m_calibration_process_handle.is_running;
        
        case EMiddleware::FUSION:
            return m_fusion_process_handle.is_running;

        default:
            return false;
    }
}
