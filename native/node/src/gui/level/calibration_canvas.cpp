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
    GET_NODE_PROPERTY(calibration_progress_bar, ProgressBar)

    // Connect framework signal

    print_verbose(TAG"Ready.");
}

void CalibrationCanvas::_exit_tree() {
    // Disconnect framework signal

    print_verbose(TAG"Exit tree.");
}

void CalibrationCanvas::_process(double delta) {}
