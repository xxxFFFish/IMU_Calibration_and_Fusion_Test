#ifndef __MAIN_HPP
#define __MAIN_HPP

#include <godot_cpp/classes/node.hpp>

namespace godot {

namespace framework {
struct ProcessData;
} // namespace framework

class Main : public Node {
    GDCLASS(Main, Node)

protected:
    static void _bind_methods();

// Class Constructor and Engine Virtual Methods
public:
    Main();
    ~Main();

    void _ready() override;
    void _exit_tree() override;

private:
    Node *mp_current_level_node = nullptr;
    Node *mp_next_level_node = nullptr;

    framework::ProcessData *mp_process_data = nullptr;

    void parse_cmds();
    void start_level();

    // Signal handler
    void on_process_quit();
    void on_process_switch_level();
};

} // namespace godot

#endif // __MAIN_HPP
