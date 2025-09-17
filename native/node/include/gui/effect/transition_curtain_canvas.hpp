#ifndef __TRANSITION_CURTAIN_CANVAS_HPP
#define __TRANSITION_CURTAIN_CANVAS_HPP

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/shader_material.hpp>

namespace godot {

class AnimationPlayer;

namespace framework {
class SignalManager;
} // namespace framework

class TransitionCurtainCanvas : public CanvasLayer {
    GDCLASS(TransitionCurtainCanvas, CanvasLayer)

protected:
    static void _bind_methods();

public:
    TransitionCurtainCanvas();
    ~TransitionCurtainCanvas();

    void _ready() override;
    void _exit_tree() override;

private:
    // Properties
    Ref<ShaderMaterial> m_curtain_material;
    AnimationPlayer *mp_transition_player = nullptr;

    framework::SignalManager *mp_signal_manager = nullptr;

    Vector2 m_view_port_size;

    void on_transition_player_animation_finished(StringName name);

public:
    void close_curtain(Vector2 center);
    void open_curtain(Vector2 center);
};

} // namespace godot

#endif // __TRANSITION_CURTAIN_CANVAS_HPP
