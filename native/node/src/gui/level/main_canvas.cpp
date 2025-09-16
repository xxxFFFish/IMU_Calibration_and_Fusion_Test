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
    GET_AND_INIT_BUTTON_PROPERTY(
        start_calibration_button,
        mp_start_calibration_button,
        LEVEL_GUI_MAIN_START_CALIBRATION_BOTTON,
        MainCanvas::on_start_calibration_button_pressed
    )

    GET_AND_INIT_BUTTON_PROPERTY(
        start_fusion_button,
        mp_start_fusion_button,
        LEVEL_GUI_MAIN_START_FUSION_BOTTON,
        MainCanvas::on_start_fusion_button_pressed
    )

    GET_AND_INIT_BUTTON_PROPERTY(
        option_button,
        mp_option_button,
        LEVEL_GUI_MAIN_OPTION_BOTTON,
        MainCanvas::on_option_button_pressed
    )

    GET_AND_INIT_BUTTON_PROPERTY(
        quit_button,
        mp_quit_button,
        LEVEL_GUI_MAIN_QUIT_BOTTON,
        MainCanvas::on_quit_button_pressed
    )

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
