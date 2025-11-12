#include "gui/level/calibration_canvas.hpp"

#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/color_rect.hpp>
#include <godot_cpp/classes/progress_bar.hpp>
#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/button.hpp>

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
    GET_NODE_PROPERTY(status_label, Label)
    GET_NODE_PROPERTY(status_color_rect, ColorRect)

    GET_NODE_PROPERTY(gyro_x_data_label, Label)
    GET_NODE_PROPERTY(gyro_y_data_label, Label)
    GET_NODE_PROPERTY(gyro_z_data_label, Label)
    GET_NODE_PROPERTY(gyro_count_label, Label)

    GET_NODE_PROPERTY(acce_x_data_label, Label)
    GET_NODE_PROPERTY(acce_y_data_label, Label)
    GET_NODE_PROPERTY(acce_z_data_label, Label)
    GET_NODE_PROPERTY(acce_count_label, Label)

    GET_NODE_PROPERTY(mag_x_data_label, Label)
    GET_NODE_PROPERTY(mag_y_data_label, Label)
    GET_NODE_PROPERTY(mag_z_data_label, Label)
    GET_NODE_PROPERTY(mag_static_count_label, Label)
    GET_NODE_PROPERTY(mag_motion_count_label, Label)

    GET_NODE_PROPERTY(gyro_motion_flag_color_rect, ColorRect)
    GET_NODE_PROPERTY(gyro_x_square_error, Label)
    GET_NODE_PROPERTY(gyro_y_square_error, Label)
    GET_NODE_PROPERTY(gyro_z_square_error, Label)
    GET_NODE_PROPERTY(gyro_sum_square_error, Label)
    GET_NODE_PROPERTY(gyro_x_static_square_error, Label)
    GET_NODE_PROPERTY(gyro_y_static_square_error, Label)
    GET_NODE_PROPERTY(gyro_z_static_square_error, Label)
    GET_NODE_PROPERTY(gyro_sum_static_square_error, Label)

    GET_NODE_PROPERTY(acce_motion_flag_color_rect, ColorRect)
    GET_NODE_PROPERTY(acce_x_square_error, Label)
    GET_NODE_PROPERTY(acce_y_square_error, Label)
    GET_NODE_PROPERTY(acce_z_square_error, Label)
    GET_NODE_PROPERTY(acce_sum_square_error, Label)
    GET_NODE_PROPERTY(acce_x_static_square_error, Label)
    GET_NODE_PROPERTY(acce_y_static_square_error, Label)
    GET_NODE_PROPERTY(acce_z_static_square_error, Label)
    GET_NODE_PROPERTY(acce_sum_static_square_error, Label)

    GET_NODE_PROPERTY(mag_motion_flag_color_rect, ColorRect)
    GET_NODE_PROPERTY(mag_x_square_error, Label)
    GET_NODE_PROPERTY(mag_y_square_error, Label)
    GET_NODE_PROPERTY(mag_z_square_error, Label)
    GET_NODE_PROPERTY(mag_sum_square_error, Label)
    GET_NODE_PROPERTY(mag_x_static_square_error, Label)
    GET_NODE_PROPERTY(mag_y_static_square_error, Label)
    GET_NODE_PROPERTY(mag_z_static_square_error, Label)
    GET_NODE_PROPERTY(mag_sum_static_square_error, Label)

    GET_NODE_PROPERTY(calibration_progress_bar, ProgressBar)

    GET_VARIANT_PROPERTY(sampling_flag_color, COLOR)
    GET_VARIANT_PROPERTY(waiting_flag_color, COLOR)

    GET_VARIANT_PROPERTY(motion_flag_color, COLOR)
    GET_VARIANT_PROPERTY(static_flag_color, COLOR)

    GET_NODE_PROPERTY(hint_panel_container, PanelContainer)
    GET_NODE_PROPERTY(hint_label, Label)
    GET_NODE_PROPERTY(enter_button, Button)

    CONNECT_NODE_PROPERTY_SIGNAL(enter_button, pressed, CalibrationCanvas::on_enter_button_pressed)

    // Connect framework signal

    print_verbose(TAG"Ready.");
}

void CalibrationCanvas::_exit_tree() {
    // Disconnect framework signal

    print_verbose(TAG"Exit tree.");
}

void CalibrationCanvas::_process(double delta) {}

void CalibrationCanvas::on_enter_button_pressed() {
    print_verbose(TAG"On signal enter button pressed.");
}
