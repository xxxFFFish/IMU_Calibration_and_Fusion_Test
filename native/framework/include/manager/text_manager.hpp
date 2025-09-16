#ifndef __TEXT_MANAGER_HPP
#define __TEXT_MANAGER_HPP

#include <godot_cpp/classes/node.hpp>

#include "type/text_type.h"

namespace godot {

namespace framework {

class TextManager : public Node {
    GDCLASS(TextManager, Node)

private:
    static TextManager *p_instance;

public:
    static TextManager *get_instance();

protected:
    static void _bind_methods();

public:
    TextManager();
    ~TextManager();

    void _ready() override;
    void _exit_tree() override;

private:
    bool m_enabled = false;

public:
    void init();
    void deinit();

    const char *get_gui_text_key(EGuiText gui_text);
};

} // namespace framework

} // namespace godot

#endif // __TEXT_MANAGER_HPP
