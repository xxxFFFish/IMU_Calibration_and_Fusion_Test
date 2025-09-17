#include "gui/level/calibration_canvas.hpp"

#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/progress_bar.hpp>
#include <godot_cpp/classes/panel_container.hpp>

#include "macro_utility.h"

#include "manager/data_manager.hpp"
#include "manager/text_manager.hpp"

using namespace godot;

#define TAG "[CalibrationCanvas]"

void CalibrationCanvas::_bind_methods() {}

CalibrationCanvas::CalibrationCanvas() {}

CalibrationCanvas::~CalibrationCanvas() {}

void CalibrationCanvas::_ready() {
    // Check and initilize resource
    GET_AND_INIT_LABEL_PROPERTY(gyro_data_label, mp_gyro_data_label, LEVEL_GUI_CALIBRATION_GYRO_DATA_LABEL)
    GET_AND_INIT_LABEL_PROPERTY(accelerometer_data_label, mp_accelerometer_data_label, LEVEL_GUI_CALIBRATION_ACCELEROMETER_DATA_LABEL)
    GET_AND_INIT_LABEL_PROPERTY(magnetometer_data_label, mp_magnetometer_data_label, LEVEL_GUI_CALIBRATION_MAGNETOMETER_DATA_LABEL)
    GET_AND_INIT_LABEL_PROPERTY(calibration_progress_label, mp_calibration_progress_label, LEVEL_GUI_CALIBRATION_PROGRESS_LABEL)

    GET_NODE_PROPERTY(calibration_progress_bar, mp_calibration_progress_bar, ProgressBar)

    // Connect framework signal

    print_verbose(TAG"Ready.");
}

void CalibrationCanvas::_exit_tree() {
    // Disconnect framework signal

    print_verbose(TAG"Exit tree.");
}

void CalibrationCanvas::_process(double delta) {}
