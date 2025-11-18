#include "level/calibration_level.hpp"

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/scene_state.hpp>

#include "fsm_program.hpp"

#include "manager/data_manager.hpp"
#include "manager/text_manager.hpp"
#include "manager/signal_manager.hpp"
#include "manager/middleware_manager.hpp"

#include "gui/level/calibration_canvas.hpp"

#include "macro_utility.h"

using namespace godot;

#define TAG "[CalibrationLevel]"

void CalibrationLevel::_bind_methods() {}

CalibrationLevel::CalibrationLevel() {}

CalibrationLevel::~CalibrationLevel() {}

void CalibrationLevel::_ready() {
    // Check and initilize resource
    GET_NODE_PROPERTY(calibration_canvas, CalibrationCanvas);

    // Get data point
    mp_process_data = framework::DataManager::get_instance()->own_process_data();
    mp_calibration_level_data = framework::DataManager::get_instance()->own_calibration_level_data();

    // Connect framework signal
    CONNECT_FRAMEWORK_SIGNAL(CALIBRATION_HINT_ENTER, on_calibration_hint_enter);

    // Start middleware process
    if (framework::MiddlewareManager::get_instance()->run(framework::EMiddleware::CALIBRATION) == Error::OK) {
        mp_calibration_monitor_data = framework::MiddlewareManager::get_instance()->get_calibration_monitor_data();
        if (mp_calibration_monitor_data == nullptr) {
            print_error(TAG"Get calibration monitor data failed!");
        }

        mp_calibration_sampling_data = framework::MiddlewareManager::get_instance()->get_calibration_sampling_data();
        if (mp_calibration_sampling_data == nullptr) {
            print_error(TAG"Get calibration sampling data failed!");
        }

        mp_calibration_result_data = framework::MiddlewareManager::get_instance()->get_calibration_result_data();
        if (mp_calibration_result_data == nullptr) {
            print_error(TAG"Get calibration result data failed!");
        }
    } else {
        print_error(TAG"Run middleware process failed!");
    }

    // Init and start fsm program
    m_fsm_program.instantiate();

    register_fsm_status();

    m_fsm_program->start((int)framework::ECalibrationStatus::IDLE);

    print_verbose(TAG"Ready.");
}

void CalibrationLevel::_exit_tree() {
    // Stop middleware process
    framework::MiddlewareManager::get_instance()->release(framework::EMiddleware::CALIBRATION);

    // Disconnect framework signal

    print_verbose(TAG"Exit tree.");
}

void CalibrationLevel::_process(double delta) {
    static int s_frame_count = 0;

    switch (s_frame_count % 8) {
        case 0:
            transfer_gyro_data();
            break;

        case 1:
            transfer_gyro_square_error();
            break;

        case 2:
            transfer_acce_data();
            break;

        case 3:
            transfer_acce_square_error();
            break;

        case 4:
            transfer_mag_data();
            break;

        case 5:
            transfer_mag_square_error();
            break;

        case 6:
            calculate_calibration_progress();
            break;

        default:;
    }

    s_frame_count++;

    m_fsm_program->process(delta);
}

void CalibrationLevel::register_fsm_status() {
    m_fsm_program->register_status(
        (int)framework::ECalibrationStatus::IDLE,
        [this]() { // Enter action
            print_verbose(TAG"Enter IDLE");
            m_hint_enter_flag = false;
            mp_calibration_canvas->show_hint_panel(
                framework::TextManager::get_instance()->get_gui_text_key(framework::EGuiText::CALIBRATION_HINT_BEFORE_PRE_SAMPLING)
            );
            mp_calibration_level_data->calibration_status = framework::ECalibrationStatus::IDLE;
        },
        nullptr, // Process action
        nullptr, // Exit action
        [this]() { // Next status
            if (m_hint_enter_flag) {
                return (int)framework::ECalibrationStatus::PRE_SAMPLING;
            }

            return (int)framework::ECalibrationStatus::IDLE;
        }
    );

    m_fsm_program->register_status(
        (int)framework::ECalibrationStatus::PRE_SAMPLING,
        [this]() { // Enter action
            print_verbose(TAG"Enter PRE_SAMPLING");
        },
        [this](double delta) { // Process action
            
        },
        [this]() { // Exit action
            
        },
        [this]() { // Next status
            return (int)framework::ECalibrationStatus::PRE_SAMPLING;
        }
    );

    m_fsm_program->register_status(
        (int)framework::ECalibrationStatus::PRE_SAMPLING_END,
        [this]() { // Enter action
            print_verbose(TAG"Enter PRE_SAMPLING_END");
        },
        [this](double delta) { // Process action
            
        },
        [this]() { // Exit action
            
        },
        [this]() { // Next status
            return (int)framework::ECalibrationStatus::PRE_SAMPLING_END;
        }
    );
}

void CalibrationLevel::transfer_gyro_data() {
    mp_calibration_level_data->gyro_raw_data[0] = mp_calibration_monitor_data->gyro_raw_data[0];
    mp_calibration_level_data->gyro_raw_data[1] = mp_calibration_monitor_data->gyro_raw_data[1];
    mp_calibration_level_data->gyro_raw_data[2] = mp_calibration_monitor_data->gyro_raw_data[2];
    mp_calibration_level_data->gyro_sampling_count = mp_calibration_monitor_data->gyro_sampling_count;
}

void CalibrationLevel::transfer_gyro_square_error() {
    mp_calibration_level_data->gyro_static_square_error[0] = (float)mp_calibration_monitor_data->gyro_static_square_error[0];
    mp_calibration_level_data->gyro_static_square_error[1] = (float)mp_calibration_monitor_data->gyro_static_square_error[1];
    mp_calibration_level_data->gyro_static_square_error[2] = (float)mp_calibration_monitor_data->gyro_static_square_error[2];
    mp_calibration_level_data->gyro_static_square_error[3] = (float)mp_calibration_monitor_data->gyro_static_square_error[3];

    mp_calibration_level_data->gyro_square_error[0] = (float)mp_calibration_monitor_data->gyro_square_error[0];
    mp_calibration_level_data->gyro_square_error[1] = (float)mp_calibration_monitor_data->gyro_square_error[1];
    mp_calibration_level_data->gyro_square_error[2] = (float)mp_calibration_monitor_data->gyro_square_error[2];
    mp_calibration_level_data->gyro_square_error[3] = (float)mp_calibration_monitor_data->gyro_square_error[3];

    mp_calibration_level_data->gyro_static_motion_flag = mp_calibration_monitor_data->gyro_static_motion_flag == 0;
}

void CalibrationLevel::transfer_acce_data() {
    mp_calibration_level_data->acce_raw_data[0] = mp_calibration_monitor_data->acce_raw_data[0];
    mp_calibration_level_data->acce_raw_data[1] = mp_calibration_monitor_data->acce_raw_data[1];
    mp_calibration_level_data->acce_raw_data[2] = mp_calibration_monitor_data->acce_raw_data[2];
    mp_calibration_level_data->acce_sampling_count = mp_calibration_monitor_data->acce_sampling_count;
}

void CalibrationLevel::transfer_acce_square_error() {
    mp_calibration_level_data->acce_static_square_error[0] = (float)mp_calibration_monitor_data->acce_static_square_error[0];
    mp_calibration_level_data->acce_static_square_error[1] = (float)mp_calibration_monitor_data->acce_static_square_error[1];
    mp_calibration_level_data->acce_static_square_error[2] = (float)mp_calibration_monitor_data->acce_static_square_error[2];
    mp_calibration_level_data->acce_static_square_error[3] = (float)mp_calibration_monitor_data->acce_static_square_error[3];

    mp_calibration_level_data->acce_square_error[0] = (float)mp_calibration_monitor_data->acce_square_error[0];
    mp_calibration_level_data->acce_square_error[1] = (float)mp_calibration_monitor_data->acce_square_error[1];
    mp_calibration_level_data->acce_square_error[2] = (float)mp_calibration_monitor_data->acce_square_error[2];
    mp_calibration_level_data->acce_square_error[3] = (float)mp_calibration_monitor_data->acce_square_error[3];

    mp_calibration_level_data->acce_static_motion_flag = mp_calibration_monitor_data->acce_static_motion_flag == 0;
}

void CalibrationLevel::transfer_mag_data() {
    mp_calibration_level_data->mag_raw_data[0] = mp_calibration_monitor_data->mag_raw_data[0];
    mp_calibration_level_data->mag_raw_data[1] = mp_calibration_monitor_data->mag_raw_data[1];
    mp_calibration_level_data->mag_raw_data[2] = mp_calibration_monitor_data->mag_raw_data[2];
    mp_calibration_level_data->mag_static_sampling_count = mp_calibration_monitor_data->mag_static_sampling_count;
    mp_calibration_level_data->mag_motion_sampling_count = mp_calibration_monitor_data->mag_motion_sampling_count;
}

void CalibrationLevel::transfer_mag_square_error() {
    mp_calibration_level_data->mag_static_square_error[0] = (float)mp_calibration_monitor_data->mag_static_square_error[0];
    mp_calibration_level_data->mag_static_square_error[1] = (float)mp_calibration_monitor_data->mag_static_square_error[1];
    mp_calibration_level_data->mag_static_square_error[2] = (float)mp_calibration_monitor_data->mag_static_square_error[2];
    mp_calibration_level_data->mag_static_square_error[3] = (float)mp_calibration_monitor_data->mag_static_square_error[3];

    mp_calibration_level_data->mag_square_error[0] = (float)mp_calibration_monitor_data->mag_square_error[0];
    mp_calibration_level_data->mag_square_error[1] = (float)mp_calibration_monitor_data->mag_square_error[1];
    mp_calibration_level_data->mag_square_error[2] = (float)mp_calibration_monitor_data->mag_square_error[2];
    mp_calibration_level_data->mag_square_error[3] = (float)mp_calibration_monitor_data->mag_square_error[3];

    mp_calibration_level_data->mag_static_motion_flag = mp_calibration_monitor_data->mag_static_motion_flag == 0;
}

void CalibrationLevel::calculate_calibration_progress() {
    
}

void CalibrationLevel::on_calibration_hint_enter() {
    print_verbose(TAG"On signal calibration hint enter.");
    m_hint_enter_flag = true;
}
