#ifndef __MAIN_CANVAS_HPP
#define __MAIN_CANVAS_HPP

#include <godot_cpp/classes/canvas_layer.hpp>

namespace godot {

class Button;

namespace framework {
struct ProcessData;
} // namespace framework

class MainCanvas : public CanvasLayer {
    GDCLASS(MainCanvas, CanvasLayer)

protected:
    static void _bind_methods();

// Class Constructor and Engine Virtual Methods
public:
    MainCanvas();
    ~MainCanvas();

    void _ready() override;
    void _exit_tree() override;

private:
    // Properties
    Button *mp_start_calibration_button = nullptr;
    Button *mp_start_fusion_button = nullptr;

    Button *mp_option_button = nullptr;
    Button *mp_quit_button = nullptr;

    framework::ProcessData *mp_process_data = nullptr;

    // Signal handler
    void on_start_calibration_button_pressed();
    void on_start_fusion_button_pressed();
    void on_option_button_pressed();
    void on_quit_button_pressed();
};

} // namespace godot

#endif // __MAIN_CANVAS_HPP
