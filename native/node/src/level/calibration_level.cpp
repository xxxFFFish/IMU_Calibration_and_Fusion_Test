#include "level/calibration_level.hpp"

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/scene_state.hpp>

#include "manager/data_manager.hpp"
#include "manager/signal_manager.hpp"
#include "manager/middleware_manager.hpp"

#include "fsm_program.hpp"
#include "context/calibration_fsm_context.hpp"

using namespace godot;

#define TAG "[CalibrationLevel]"

void CalibrationLevel::_bind_methods() {}

CalibrationLevel::CalibrationLevel() {}

CalibrationLevel::~CalibrationLevel() {}

void CalibrationLevel::_ready() {
    // Check and initilize resource

    // Get data point
    mp_process_data = framework::DataManager::get_instance()->own_process_data();

    // Connect framework signal

    // Start middleware process
    if (framework::MiddlewareManager::get_instance()->run(framework::EMiddleware::CALIBRATION) != Error::OK) {
        print_error(TAG"Run middleware process failed!");
    }

    // Init and start fsm program
    m_fsm_program.instantiate();
    Ref<framework::CalibrationFsmContext> calibration_fsm_context;
    calibration_fsm_context.instantiate();
    Ref<FsmContext> cast_fsm_context = calibration_fsm_context;
    m_fsm_program->set_context(cast_fsm_context);

    register_fsm_status();

    m_fsm_program->start((int)framework::CalibrationFsmContext::ECalibrationFsmStatus::IDLE);

    print_verbose(TAG"Ready.");
}

void CalibrationLevel::_exit_tree() {
    // Stop middleware process
    if (framework::MiddlewareManager::get_instance()->is_running(framework::EMiddleware::CALIBRATION)) {
        framework::MiddlewareManager::get_instance()->stop(framework::EMiddleware::CALIBRATION);
    }

    // Disconnect framework signal

    print_verbose(TAG"Exit tree.");
}

void CalibrationLevel::_process(double delta) {
    m_fsm_program->process();
}

void CalibrationLevel::register_fsm_status() {
    m_fsm_program->register_status(
        (int)framework::CalibrationFsmContext::ECalibrationFsmStatus::IDLE,
        [](Ref<FsmContext> &context) { // Enter action
            print_verbose(TAG"Enter IDLE");
        },
        [](Ref<FsmContext> &context) { // Process action
            print_verbose(TAG"Process IDLE");
        },
        [](Ref<FsmContext> &context) { // Exit action
            print_verbose(TAG"Exit IDLE");
        },
        [](Ref<FsmContext> &context) { // Next status
            return (int)framework::CalibrationFsmContext::ECalibrationFsmStatus::IDLE;
        }
    );

    m_fsm_program->register_status(
        (int)framework::CalibrationFsmContext::ECalibrationFsmStatus::PRE_SAMPLING,
        [](Ref<FsmContext> &context) { // Enter action
            print_verbose(TAG"Enter PRE_SAMPLING");
        },
        [](Ref<FsmContext> &context) { // Process action
            print_verbose(TAG"Process PRE_SAMPLING");
        },
        [](Ref<FsmContext> &context) { // Exit action
            print_verbose(TAG"Exit PRE_SAMPLING");
        },
        [](Ref<FsmContext> &context) { // Next status
            return (int)framework::CalibrationFsmContext::ECalibrationFsmStatus::PRE_SAMPLING;
        }
    );

    m_fsm_program->register_status(
        (int)framework::CalibrationFsmContext::ECalibrationFsmStatus::PRE_SAMPLING_END,
        [](Ref<FsmContext> &context) { // Enter action
            print_verbose(TAG"Enter PRE_SAMPLING_END");
        },
        [](Ref<FsmContext> &context) { // Process action
            print_verbose(TAG"Process PRE_SAMPLING_END");
        },
        [](Ref<FsmContext> &context) { // Exit action
            print_verbose(TAG"Exit PRE_SAMPLING_END");
        },
        [](Ref<FsmContext> &context) { // Next status
            return (int)framework::CalibrationFsmContext::ECalibrationFsmStatus::PRE_SAMPLING_END;
        }
    );
}
