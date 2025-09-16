#ifndef __GUI_MANAGER_HPP
#define __GUI_MANAGER_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "type/gui_type.h"

namespace godot {

class CanvasLayer;

namespace framework {

class GuiManager : public Node {
    GDCLASS(GuiManager, Node)

private:
    static GuiManager *p_instance;

public:
    static GuiManager *get_instance();

protected:
    static void _bind_methods();

public:
    GuiManager();
    ~GuiManager();

    void _ready() override;
    void _exit_tree() override;

private:
    Ref<PackedScene> m_option_canvas_packed_scene;
    Ref<PackedScene> m_transition_curtain_canvas_packed_scene;

public:
    void init();
    void deinit();

    CanvasLayer *instantiate_gui(EGuiCanvas gui);
};

} // namespace framework

} // namespace godot

#endif // __GUI_MANAGER_HPP
