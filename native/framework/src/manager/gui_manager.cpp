#include "manager/gui_manager.hpp"

#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/scene_state.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>

#include "macro_utility.h"

// #include "gui/float/option_canvas.hpp"
#include "gui/effect/transition_curtain_canvas.hpp"

using namespace godot;
using namespace framework;

#define TAG "[GuiManager]"

GuiManager *GuiManager::p_instance = nullptr;

GuiManager *GuiManager::get_instance() {
    RETURN_INSTANCE()
}

void GuiManager::_bind_methods() {}

GuiManager::GuiManager() {
    INIT_INSTANCE()
    print_verbose(TAG"Created.");
}

GuiManager::~GuiManager() {
    p_instance = nullptr;
}

void GuiManager::_ready() {
    // Check resource
    // GET_PACKED_SCENE_PROPERTY(option_canvas_packed_scene, m_option_canvas_packed_scene, OptionCanvas)
    GET_PACKED_SCENE_PROPERTY(transition_curtain_canvas_packed_scene, m_transition_curtain_canvas_packed_scene, TransitionCurtainCanvas)

    print_verbose(TAG"Ready.");
}

void GuiManager::_exit_tree() {
    print_verbose(TAG"Exit tree.");
}

void GuiManager::init() {
    print_verbose(TAG"Init.");
}

void GuiManager::deinit() {
    print_verbose(TAG"Deinit.");
}

CanvasLayer *GuiManager::instantiate_gui(EGuiCanvas gui) {
    Node *instance = nullptr;

    switch (gui) {
        // case EGuiCanvas::OPTION:
        //     if (likely(!m_option_canvas_packed_scene.is_null())) {
        //         instance = m_option_canvas_packed_scene->instantiate();
        //     }
        //     break;

        case EGuiCanvas::TRANSITION_CURTAIN:
            if (likely(!m_transition_curtain_canvas_packed_scene.is_null())) {
                instance = m_transition_curtain_canvas_packed_scene->instantiate();
            }
            break;

        default:;
    }

    return Object::cast_to<CanvasLayer>(instance);
}
