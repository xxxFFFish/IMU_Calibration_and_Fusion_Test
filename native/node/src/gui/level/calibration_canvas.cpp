#include "gui/level/calibration_canvas.hpp"

#include <cstdio>

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
    GET_NODE_PROPERTY(gyro_x_square_error_label, Label)
    GET_NODE_PROPERTY(gyro_y_square_error_label, Label)
    GET_NODE_PROPERTY(gyro_z_square_error_label, Label)
    GET_NODE_PROPERTY(gyro_sum_square_error_label, Label)
    GET_NODE_PROPERTY(gyro_x_static_square_error_label, Label)
    GET_NODE_PROPERTY(gyro_y_static_square_error_label, Label)
    GET_NODE_PROPERTY(gyro_z_static_square_error_label, Label)
    GET_NODE_PROPERTY(gyro_sum_static_square_error_label, Label)

    GET_NODE_PROPERTY(acce_motion_flag_color_rect, ColorRect)
    GET_NODE_PROPERTY(acce_x_square_error_label, Label)
    GET_NODE_PROPERTY(acce_y_square_error_label, Label)
    GET_NODE_PROPERTY(acce_z_square_error_label, Label)
    GET_NODE_PROPERTY(acce_sum_square_error_label, Label)
    GET_NODE_PROPERTY(acce_x_static_square_error_label, Label)
    GET_NODE_PROPERTY(acce_y_static_square_error_label, Label)
    GET_NODE_PROPERTY(acce_z_static_square_error_label, Label)
    GET_NODE_PROPERTY(acce_sum_static_square_error_label, Label)

    GET_NODE_PROPERTY(mag_motion_flag_color_rect, ColorRect)
    GET_NODE_PROPERTY(mag_x_square_error_label, Label)
    GET_NODE_PROPERTY(mag_y_square_error_label, Label)
    GET_NODE_PROPERTY(mag_z_square_error_label, Label)
    GET_NODE_PROPERTY(mag_sum_square_error_label, Label)
    GET_NODE_PROPERTY(mag_x_static_square_error_label, Label)
    GET_NODE_PROPERTY(mag_y_static_square_error_label, Label)
    GET_NODE_PROPERTY(mag_z_static_square_error_label, Label)
    GET_NODE_PROPERTY(mag_sum_static_square_error_label, Label)

    GET_NODE_PROPERTY(calibration_progress_bar, ProgressBar)

    GET_VARIANT_PROPERTY(sampling_flag_color, COLOR)
    GET_VARIANT_PROPERTY(waiting_flag_color, COLOR)

    GET_VARIANT_PROPERTY(motion_flag_color, COLOR)
    GET_VARIANT_PROPERTY(static_flag_color, COLOR)

    GET_NODE_PROPERTY(hint_panel_container, PanelContainer)
    GET_NODE_PROPERTY(hint_label, Label)
    GET_NODE_PROPERTY(enter_button, Button)

    CONNECT_NODE_PROPERTY_SIGNAL(enter_button, pressed, CalibrationCanvas::on_enter_button_pressed)

    // Get data point
    mp_calibration_level_data = framework::DataManager::get_instance()->get_calibration_level_data();

    // Connect framework signal

    print_verbose(TAG"Ready.");
}

void CalibrationCanvas::_exit_tree() {
    // Disconnect framework signal

    print_verbose(TAG"Exit tree.");
}

void CalibrationCanvas::_process(double delta) {
    static int s_frame_count = 0;

    switch (s_frame_count % 8) {
        case 0:
            update_status();
            break;

        case 1:
            update_gyro_data();
            break;

        case 2:
            update_gyro_square_error();
            break;

        case 3:
            update_acce_data();
            break;

        case 4:
            update_acce_square_error();
            break;

        case 5:
            update_mag_data();
            break;

        case 6:
            update_mag_square_error();
            break;

        case 7:
            update_calibration_progress();
            break;

        default:;
    }

    s_frame_count++;
}

void CalibrationCanvas::update_status() {
    switch (mp_calibration_level_data->calibration_status) {
        case framework::ECalibrationStatus::IDLE:
            mp_status_label->set_text("IDLE");
            mp_status_color_rect->set_color(m_waiting_flag_color);
            break;

        case framework::ECalibrationStatus::PRE_SAMPLING:
            mp_status_label->set_text("PRE_SAMPLING");
            mp_status_color_rect->set_color(m_sampling_flag_color);
            break;

        case framework::ECalibrationStatus::PRE_SAMPLING_END:
            mp_status_label->set_text("PRE_SAMPLING_END");
            mp_status_color_rect->set_color(m_waiting_flag_color);
            break;

        case framework::ECalibrationStatus::MOTION_SAMPLING:
            mp_status_label->set_text("MOTION_SAMPLING");
            mp_status_color_rect->set_color(m_sampling_flag_color);
            break;

        case framework::ECalibrationStatus::STATIC_SAMPLING:
            mp_status_label->set_text("STATIC_SAMPLING");
            mp_status_color_rect->set_color(m_sampling_flag_color);
            break;

        case framework::ECalibrationStatus::STATIC_SAMPLING_END:
            mp_status_label->set_text("STATIC_SAMPLING_END");
            mp_status_color_rect->set_color(m_waiting_flag_color);
            break;

        case framework::ECalibrationStatus::SAMPLING_END:
            mp_status_label->set_text("SAMPLING_END");
            mp_status_color_rect->set_color(m_waiting_flag_color);
            break;

        case framework::ECalibrationStatus::AWAIT_RESULT:
            mp_status_label->set_text("AWAIT_RESULT");
            mp_status_color_rect->set_color(m_waiting_flag_color);
            break;

        case framework::ECalibrationStatus::CALIBRATION_END:
            mp_status_label->set_text("CALIBRATION_END");
            mp_status_color_rect->set_color(m_waiting_flag_color);
            break;

        default:
            mp_status_label->set_text("ERROR");
            mp_status_color_rect->set_color(m_waiting_flag_color);
            break;
    }
}

void CalibrationCanvas::update_gyro_data() {
    mp_gyro_x_data_label->set_text(String::num_int64(mp_calibration_level_data->gyro_raw_data[0]));
    mp_gyro_y_data_label->set_text(String::num_int64(mp_calibration_level_data->gyro_raw_data[1]));
    mp_gyro_z_data_label->set_text(String::num_int64(mp_calibration_level_data->gyro_raw_data[2]));

    mp_gyro_count_label->set_text(
        String::num_int64(mp_calibration_level_data->gyro_sampling_count) + 
        " / " +
        String::num_int64(mp_calibration_level_data->gyro_target_sampling_quantity)
    );
}

void CalibrationCanvas::update_gyro_square_error() {
    if (mp_calibration_level_data->gyro_static_motion_flag) {
        mp_gyro_motion_flag_color_rect->set_color(m_motion_flag_color);
    } else {
        mp_gyro_motion_flag_color_rect->set_color(m_static_flag_color);
    }

    char num_buffer[16];
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->gyro_square_error[0]);
    mp_gyro_x_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->gyro_square_error[1]);
    mp_gyro_y_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->gyro_square_error[2]);
    mp_gyro_z_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->gyro_square_error[3]);
    mp_gyro_sum_square_error_label->set_text(String(num_buffer));

    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->gyro_static_square_error[0]);
    mp_gyro_x_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->gyro_static_square_error[1]);
    mp_gyro_y_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->gyro_static_square_error[2]);
    mp_gyro_z_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->gyro_static_square_error[3]);
    mp_gyro_sum_static_square_error_label->set_text(String(num_buffer));
}

void CalibrationCanvas::update_acce_data() {
    mp_acce_x_data_label->set_text(String::num_int64(mp_calibration_level_data->acce_raw_data[0]));
    mp_acce_y_data_label->set_text(String::num_int64(mp_calibration_level_data->acce_raw_data[1]));
    mp_acce_z_data_label->set_text(String::num_int64(mp_calibration_level_data->acce_raw_data[2]));

    mp_acce_count_label->set_text(
        String::num_int64(mp_calibration_level_data->acce_sampling_count) + 
        " / " +
        String::num_int64(mp_calibration_level_data->acce_target_sampling_quantity)
    );
}

void CalibrationCanvas::update_acce_square_error() {
    if (mp_calibration_level_data->acce_static_motion_flag) {
        mp_acce_motion_flag_color_rect->set_color(m_motion_flag_color);
    } else {
        mp_acce_motion_flag_color_rect->set_color(m_static_flag_color);
    }

    char num_buffer[16];
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->acce_square_error[0]);
    mp_acce_x_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->acce_square_error[1]);
    mp_acce_y_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->acce_square_error[2]);
    mp_acce_z_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->acce_square_error[3]);
    mp_acce_sum_square_error_label->set_text(String(num_buffer));

    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->acce_static_square_error[0]);
    mp_acce_x_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->acce_static_square_error[1]);
    mp_acce_y_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->acce_static_square_error[2]);
    mp_acce_z_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->acce_static_square_error[3]);
    mp_acce_sum_static_square_error_label->set_text(String(num_buffer));
}
void CalibrationCanvas::update_mag_data() {
    mp_mag_x_data_label->set_text(String::num_int64(mp_calibration_level_data->mag_raw_data[0]));
    mp_mag_y_data_label->set_text(String::num_int64(mp_calibration_level_data->mag_raw_data[1]));
    mp_mag_z_data_label->set_text(String::num_int64(mp_calibration_level_data->mag_raw_data[2]));

    mp_mag_static_count_label->set_text(
        String::num_int64(mp_calibration_level_data->mag_static_sampling_count) + 
        " / " +
        String::num_int64(mp_calibration_level_data->mag_target_static_sampling_quantity)
    );

    mp_mag_motion_count_label->set_text(
        String::num_int64(mp_calibration_level_data->mag_motion_sampling_count) + 
        " / " +
        String::num_int64(mp_calibration_level_data->mag_target_motion_sampling_quantity)
    );
}

void CalibrationCanvas::update_mag_square_error() {
    if (mp_calibration_level_data->mag_static_motion_flag) {
        mp_mag_motion_flag_color_rect->set_color(m_motion_flag_color);
    } else {
        mp_mag_motion_flag_color_rect->set_color(m_static_flag_color);
    }

    char num_buffer[16];
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->mag_square_error[0]);
    mp_mag_x_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->mag_square_error[1]);
    mp_mag_y_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->mag_square_error[2]);
    mp_mag_z_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->mag_square_error[3]);
    mp_mag_sum_square_error_label->set_text(String(num_buffer));

    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->mag_static_square_error[0]);
    mp_mag_x_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->mag_static_square_error[1]);
    mp_mag_y_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->mag_static_square_error[2]);
    mp_mag_z_static_square_error_label->set_text(String(num_buffer));
    snprintf(num_buffer, sizeof(num_buffer), "%.4e", mp_calibration_level_data->mag_static_square_error[3]);
    mp_mag_sum_static_square_error_label->set_text(String(num_buffer));
}

void CalibrationCanvas::update_calibration_progress() {
    mp_calibration_progress_bar->set_value(mp_calibration_level_data->calibration_progress);
}

void CalibrationCanvas::on_enter_button_pressed() {
    print_verbose(TAG"On signal enter button pressed.");
}
