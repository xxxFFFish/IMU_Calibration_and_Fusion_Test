#include "level/calibration_level.hpp"

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/scene_state.hpp>

#include "fsm_program.hpp"

#include "manager/data_manager.hpp"
#include "manager/signal_manager.hpp"
#include "manager/middleware_manager.hpp"

using namespace godot;

#define TAG "[CalibrationLevel]"

void CalibrationLevel::_bind_methods() {}

CalibrationLevel::CalibrationLevel() {}

CalibrationLevel::~CalibrationLevel() {}

void CalibrationLevel::_ready() {
    // Check and initilize resource

    // Get data point
    mp_process_data = framework::DataManager::get_instance()->own_process_data();
    mp_calibration_level_data = framework::DataManager::get_instance()->own_calibration_level_data();

    // Connect framework signal

    // Start middleware process
    if (framework::MiddlewareManager::get_instance()->run(framework::EMiddleware::CALIBRATION) == Error::OK) {
        mp_calibration_monitor_data = framework::MiddlewareManager::get_instance()->get_calibration_monitor_data();
        if (mp_calibration_monitor_data == nullptr) {
            print_error(TAG"Get calibration monitor data failed!");
            return;
        }

        mp_calibration_sampling_data = framework::MiddlewareManager::get_instance()->get_calibration_sampling_data();
        if (mp_calibration_sampling_data == nullptr) {
            print_error(TAG"Get calibration sampling data failed!");
            return;
        }

        mp_calibration_result_data = framework::MiddlewareManager::get_instance()->get_calibration_result_data();
        if (mp_calibration_result_data == nullptr) {
            print_error(TAG"Get calibration result data failed!");
            return;
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
    m_fsm_program->process(delta);
}

void CalibrationLevel::register_fsm_status() {
    m_fsm_program->register_status(
        (int)framework::ECalibrationStatus::IDLE,
        [this]() { // Enter action
            print_verbose(TAG"Enter IDLE");
        },
        [this](double delta) { // Process action
            
        },
        [this]() { // Exit action
            
        },
        [this]() { // Next status
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
