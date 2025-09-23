#ifndef __CHIEF_MANAGER_HPP
#define __CHIEF_MANAGER_HPP

#include <godot_cpp/classes/node.hpp>

namespace godot {

namespace framework {

class DataManager;
class TextManager;
class SignalManager;
class LevelManager;
class GuiManager;
class MiddlewareManager;

class ChiefManager : public Node {
    GDCLASS(ChiefManager, Node)

private:
    static ChiefManager *p_instance;

public:
    static ChiefManager *get_instance();

protected:
    static void _bind_methods();

public:
    ChiefManager();
    ~ChiefManager();

    void _ready() override;
    void _exit_tree() override;

private:
    DataManager *mp_data_manager = nullptr;
    TextManager *mp_text_manager = nullptr;
    SignalManager *mp_signal_manager = nullptr;
    LevelManager *mp_level_manager = nullptr;
    GuiManager *mp_gui_manager = nullptr;
    MiddlewareManager *mp_middleware_manager = nullptr;

public:
    void init();
    void deinit();
};

} // namespace framework

} // namespace godot

#endif // __CHIEF_MANAGER_HPP
