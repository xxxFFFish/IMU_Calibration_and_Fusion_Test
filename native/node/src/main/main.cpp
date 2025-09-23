#include "main/main.hpp"

#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/translation_server.hpp>
#include <godot_cpp/classes/scene_state.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "macro_utility.h"

#include "manager/chief_manager.hpp"
#include "manager/data_manager.hpp"
#include "manager/text_manager.hpp"
#include "manager/signal_manager.hpp"
#include "manager/level_manager.hpp"
#include "manager/gui_manager.hpp"

#include "gui/effect/transition_curtain_canvas.hpp"

using namespace godot;

#define TAG "[Main]"

void Main::_bind_methods() {}

Main::Main() {}

Main::~Main() {}

void Main::_ready() {
    print_verbose(TAG"Ready begin.");

    // Initilize framework autoload node
    framework::ChiefManager *p_chief_manager = framework::ChiefManager::get_instance();
    if (p_chief_manager) {
        p_chief_manager->init();
    } else {
        print_error(TAG"ChiefManager instance is null!");
    }

    // Get data point
    mp_process_data = framework::DataManager::get_instance()->own_process_data();

    // Connect framework signal
    CONNECT_FRAMEWORK_SIGNAL(PROCESS_QUIT, Main::on_process_quit)
    CONNECT_FRAMEWORK_SIGNAL(PROCESS_SWITCH_LEVEL, Main::on_process_switch_level)
    CONNECT_FRAMEWORK_SIGNAL(CURTAIN_CLOSE_FINISHED, Main::on_curtain_close_finished)
    CONNECT_FRAMEWORK_SIGNAL(CURTAIN_OPEN_FINISHED, Main::on_curtain_open_finished)

    // Start application
    parse_cmds();
    start_level();

    print_verbose(TAG"Ready end.");
}

void Main::_exit_tree() {
    print_verbose(TAG"Exit tree begin.");

    // Disconnect framework signal
    DISCONNECT_FRAMEWORK_SIGNAL(PROCESS_QUIT, Main::on_process_quit)
    DISCONNECT_FRAMEWORK_SIGNAL(PROCESS_SWITCH_LEVEL, Main::on_process_switch_level)

    // Deinitilize framework autoload node
    framework::ChiefManager *p_chief_manager = framework::ChiefManager::get_instance();
    if (p_chief_manager) {
        p_chief_manager->deinit();
    } else {
        print_error(TAG"Chief instance is null!");
    }

    print_verbose(TAG"Exit tree end.");
}

void Main::parse_cmds() {
    PackedStringArray input_cmds = OS::get_singleton()->get_cmdline_args();

    print_verbose(vformat(TAG"Input cmds: %s", input_cmds));

    for (unsigned int i = 0; i < input_cmds.size(); i++) {
        String cmd = input_cmds[i].to_upper();

        PackedStringArray cmd_buffer = cmd.split("=", true, 2);

        if (cmd_buffer.size() == 2) {
            print_verbose(vformat(TAG"Cmd %d type: %s", i, cmd_buffer[0]));

            if (cmd_buffer[0] == "MODE") {
                print_verbose(vformat(TAG"Set mode to %s.", cmd_buffer[1]));

                if (cmd_buffer[1] == "CALIBRATION") {
                    mp_process_data->start_mode = framework::EStartMode::CALIBRATION;
                } else if (cmd_buffer[1] == "FUSION") {
                    mp_process_data->start_mode = framework::EStartMode::FUSION;
                } else {
                    print_error(vformat(TAG"%s is not a valid mode setting!", cmd_buffer[1]));
                }
            }

            if (cmd_buffer[0] == "LANGUAGE") {
                print_verbose(vformat(TAG"Set language to %s.", cmd_buffer[1]));

                if (cmd_buffer[1] == "EN" || cmd_buffer[1] == "ENGLISH" ) {
                    TranslationServer::get_singleton()->set_locale("en_US");
                } else if (cmd_buffer[1] == "ZH" || cmd_buffer[1] == "ZH_CN" || cmd_buffer[1] == "CHINESE") {
                    TranslationServer::get_singleton()->set_locale("zh_CN");
                } else {
                    print_error(vformat(TAG"%s is not a valid language setting!", cmd_buffer[1]));
                }
            }
        }
    }
}

void Main::start_level() {
    framework::ELevel start_level = framework::ELevel::MAIN;

    switch (mp_process_data->start_mode) {
        case framework::EStartMode::CALIBRATION:
            start_level = framework::ELevel::CALIBRATION;
            break;

        case framework::EStartMode::FUSION:
            start_level = framework::ELevel::FUSION;
            break;

        default:;
    }

    Node *start_level_node = framework::LevelManager::get_instance()->instantiate_level(start_level);
    if (start_level_node == nullptr) {
        print_error(TAG"Instantiate start level failed!");
        return;
    }

    this->add_child(start_level_node);
    mp_current_level_node = start_level_node;
}

void Main::switch_level() {
    mp_transition_curtain_canvas = cast_to<TransitionCurtainCanvas>(
        framework::GuiManager::get_instance()->instantiate_gui(
            framework::EGuiCanvas::TRANSITION_CURTAIN
        )
    );

    if (likely(mp_transition_curtain_canvas)) {
        this->add_child(mp_transition_curtain_canvas);
        mp_transition_curtain_canvas->close_curtain(this->get_viewport()->get_mouse_position());
    } else {
        print_error(TAG"Instantiate transition curtain canvas failed!");

        if (mp_current_level_node) {
            mp_current_level_node->queue_free();
        }
    
        this->add_child(mp_next_level_node);
        mp_current_level_node = mp_next_level_node;

        mp_process_data->current_level = mp_process_data->next_level;
    }
}

void Main::on_process_quit() {
    print_verbose(TAG"On signal process quit.");
}

void Main::on_process_switch_level() {
    print_verbose(TAG"On signal switch level.");

    if (mp_process_data->current_level != mp_process_data->next_level) {
        mp_next_level_node = framework::LevelManager::get_instance()->instantiate_level(mp_process_data->next_level);
        if (likely(mp_next_level_node)) {
            switch_level();
        } else {
            print_error(vformat(TAG"Instantiate level %d failed!", static_cast<int>(mp_process_data->next_level)));
        }
    }
}

void Main::on_curtain_close_finished() {
    print_verbose(TAG"On signal curtain close finished.");

    if (mp_current_level_node) {
        mp_current_level_node->queue_free();
    }

    this->add_child(mp_next_level_node);
    mp_current_level_node = mp_next_level_node;
    mp_next_level_node = nullptr;

    mp_process_data->current_level = mp_process_data->next_level;

    mp_transition_curtain_canvas->open_curtain(this->get_viewport()->get_mouse_position());
}

void Main::on_curtain_open_finished() {
    print_verbose(TAG"On signal curtain open finished.");

    mp_transition_curtain_canvas->queue_free();
    mp_transition_curtain_canvas = nullptr;
}
