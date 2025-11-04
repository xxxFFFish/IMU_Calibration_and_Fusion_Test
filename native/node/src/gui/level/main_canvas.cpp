#include "gui/level/main_canvas.hpp"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>

#include "macro_utility.h"
#include "type/gui_type.h"

#include "manager/data_manager.hpp"
#include "manager/text_manager.hpp"
#include "manager/signal_manager.hpp"
#include "manager/gui_manager.hpp"

using namespace godot;

#define TAG "[MainCanvas]"

void MainCanvas::_bind_methods() {}

MainCanvas::MainCanvas() {}

MainCanvas::~MainCanvas() {}

void MainCanvas::_ready() {
    // Check and initilize resource
    GET_NODE_PROPERTY(start_calibration_button, Button)
    GET_NODE_PROPERTY(start_fusion_button, Button)
    GET_NODE_PROPERTY(option_button, Button)
    GET_NODE_PROPERTY(quit_button, Button)

    CONNECT_NODE_PROPERTY_SIGNAL(start_calibration_button, pressed, MainCanvas::on_start_calibration_button_pressed)
    CONNECT_NODE_PROPERTY_SIGNAL(start_fusion_button, pressed, MainCanvas::on_start_fusion_button_pressed)
    CONNECT_NODE_PROPERTY_SIGNAL(option_button, pressed, MainCanvas::on_option_button_pressed)
    CONNECT_NODE_PROPERTY_SIGNAL(quit_button, pressed, MainCanvas::on_quit_button_pressed)

    // Get data point
    mp_process_data = framework::DataManager::get_instance()->own_process_data();

    // Connect framework signal

    print_verbose(TAG"Ready.");
}

void MainCanvas::_exit_tree() {
    // Disconnect framework signal

    print_verbose(TAG"Exit tree.");
}

void MainCanvas::on_start_calibration_button_pressed() {
    print_verbose(TAG"On signal start calibration button pressed.");

    mp_process_data->next_level = framework::ELevel::CALIBRATION;
    framework::SignalManager::get_instance()->signal_emit(framework::ESignal::PROCESS_SWITCH_LEVEL);
}

void MainCanvas::on_start_fusion_button_pressed() {
    print_verbose(TAG"On signal start fusion button pressed.");

    mp_process_data->next_level = framework::ELevel::FUSION;
    framework::SignalManager::get_instance()->signal_emit(framework::ESignal::PROCESS_SWITCH_LEVEL);
}

void MainCanvas::on_option_button_pressed() {
    print_verbose(TAG"On signal Option button pressed.");

    CanvasLayer *canvas = framework::GuiManager::get_instance()->instantiate_gui(framework::EGuiCanvas::OPTION);
    if (canvas == nullptr) {
        print_error(TAG"Instantiate option failed!");
        return;
    }

    this->add_child(canvas);
}

void MainCanvas::on_quit_button_pressed() {
    print_verbose(TAG"On signal Quit button pressed.");

    framework::SignalManager::get_instance()->signal_emit_deferred(framework::ESignal::PROCESS_QUIT);
}
