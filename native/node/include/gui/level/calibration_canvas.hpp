#ifndef __CALIBRATION_CANVAS_HPP
#define __CALIBRATION_CANVAS_HPP

#include <godot_cpp/classes/canvas_layer.hpp>

namespace godot {

class Label;
class ColorRect;
class ProgressBar;
class PanelContainer;
class Button;

namespace framework {
struct ImuReceiverData;
} // namespace framework

class CalibrationCanvas : public CanvasLayer {
    GDCLASS(CalibrationCanvas, CanvasLayer)

protected:
    static void _bind_methods();

public:
    CalibrationCanvas();
    ~CalibrationCanvas();

    void _ready() override;
    void _exit_tree() override;
    void _process(double delta) override;

private:
    // Properties
    Label *mp_status_label = nullptr;
    ColorRect *mp_status_color_rect = nullptr;

    Label *mp_gyro_x_data_label = nullptr;
    Label *mp_gyro_y_data_label = nullptr;
    Label *mp_gyro_z_data_label = nullptr;
    Label *mp_gyro_count_label = nullptr;

    Label *mp_acce_x_data_label = nullptr;
    Label *mp_acce_y_data_label = nullptr;
    Label *mp_acce_z_data_label = nullptr;
    Label *mp_acce_count_label = nullptr;

    Label *mp_mag_x_data_label = nullptr;
    Label *mp_mag_y_data_label = nullptr;
    Label *mp_mag_z_data_label = nullptr;
    Label *mp_mag_static_count_label = nullptr;
    Label *mp_mag_motion_count_label = nullptr;

    ColorRect *mp_gyro_motion_flag_color_rect = nullptr;
    Label *mp_gyro_x_square_error = nullptr;
    Label *mp_gyro_y_square_error = nullptr;
    Label *mp_gyro_z_square_error = nullptr;
    Label *mp_gyro_sum_square_error = nullptr;
    Label *mp_gyro_x_static_square_error = nullptr;
    Label *mp_gyro_y_static_square_error = nullptr;
    Label *mp_gyro_z_static_square_error = nullptr;
    Label *mp_gyro_sum_static_square_error = nullptr;

    ColorRect *mp_acce_motion_flag_color_rect = nullptr;
    Label *mp_acce_x_square_error = nullptr;
    Label *mp_acce_y_square_error = nullptr;
    Label *mp_acce_z_square_error = nullptr;
    Label *mp_acce_sum_square_error = nullptr;
    Label *mp_acce_x_static_square_error = nullptr;
    Label *mp_acce_y_static_square_error = nullptr;
    Label *mp_acce_z_static_square_error = nullptr;
    Label *mp_acce_sum_static_square_error = nullptr;

    ColorRect *mp_mag_motion_flag_color_rect = nullptr;
    Label *mp_mag_x_square_error = nullptr;
    Label *mp_mag_y_square_error = nullptr;
    Label *mp_mag_z_square_error = nullptr;
    Label *mp_mag_sum_square_error = nullptr;
    Label *mp_mag_x_static_square_error = nullptr;
    Label *mp_mag_y_static_square_error = nullptr;
    Label *mp_mag_z_static_square_error = nullptr;
    Label *mp_mag_sum_static_square_error = nullptr;

    ProgressBar *mp_calibration_progress_bar = nullptr;

    Color m_sampling_flag_color;
    Color m_waiting_flag_color;

    Color m_motion_flag_color;
    Color m_static_flag_color;

    PanelContainer *mp_hint_panel_container = nullptr;
    Label *mp_hint_label = nullptr;
    Button *mp_enter_button = nullptr;

    // Signal handler
    void on_enter_button_pressed();
};

} // namespace godot

#endif // __CALIBRATION_CANVAS_HPP
