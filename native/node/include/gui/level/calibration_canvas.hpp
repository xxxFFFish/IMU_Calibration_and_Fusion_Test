#ifndef __CALIBRATION_CANVAS_HPP
#define __CALIBRATION_CANVAS_HPP

#include <godot_cpp/classes/canvas_layer.hpp>

namespace godot {

class Label;
class ProgressBar;

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
    Label *mp_gyro_data_label = nullptr;
    Label *mp_accelerometer_data_label = nullptr;
    Label *mp_magnetometer_data_label = nullptr;
    Label *mp_calibration_progress_label = nullptr;
    ProgressBar *mp_calibration_progress_bar = nullptr;
};

} // namespace godot

#endif // __CALIBRATION_CANVAS_HPP
