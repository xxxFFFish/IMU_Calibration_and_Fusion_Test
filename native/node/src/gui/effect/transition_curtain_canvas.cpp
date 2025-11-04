#include "gui/effect/transition_curtain_canvas.hpp"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "macro_utility.h"

#include "manager/signal_manager.hpp"

using namespace godot;

#define TAG "[TransitionCurtainCanvas]"

void TransitionCurtainCanvas::_bind_methods() {}

TransitionCurtainCanvas::TransitionCurtainCanvas() {}

TransitionCurtainCanvas::~TransitionCurtainCanvas() {}


void TransitionCurtainCanvas::_ready() {
    // Check and initilize resource
    GET_RESOURCE_PROPERTY(curtain_material)
    GET_NODE_PROPERTY(transition_player, AnimationPlayer)

    if (likely(mp_transition_player)) {
        if (mp_transition_player->connect(
            "animation_finished", callable_mp(this, &TransitionCurtainCanvas::on_transition_player_animation_finished)
        ) != Error::OK) {
            print_error(TAG"Connect transition player signal animation_finished failed");
        }
    } else {
        print_error(TAG"Transition player is null!");
    }

    // Get autoload node instance
    mp_signal_manager = framework::SignalManager::get_instance();

    // Initialize members
    m_view_port_size = this->get_viewport()->get_visible_rect().size;

    print_verbose(TAG"Ready.");
}

void TransitionCurtainCanvas::_exit_tree() {
    print_verbose(TAG"Exit tree.");
}

void TransitionCurtainCanvas::close_curtain(Vector2 center) {
    Vector2 shader_center = Vector2(center.x / m_view_port_size.x, center.y / m_view_port_size.y);

    m_curtain_material->set_shader_parameter("Anchor", shader_center);

    mp_transition_player->play("close");
}

void TransitionCurtainCanvas::open_curtain(Vector2 center) {
    Vector2 shader_center = Vector2(center.x / m_view_port_size.x, center.y / m_view_port_size.y);

    m_curtain_material->set_shader_parameter("Anchor", shader_center);

    mp_transition_player->play("open");
}

void TransitionCurtainCanvas::on_transition_player_animation_finished(StringName name) {
    if (name == StringName("close")) {
        mp_signal_manager->signal_emit(framework::ESignal::CURTAIN_CLOSE_FINISHED);
    } else if (name == StringName("open")) {
        mp_signal_manager->signal_emit(framework::ESignal::CURTAIN_OPEN_FINISHED);
    }
}
