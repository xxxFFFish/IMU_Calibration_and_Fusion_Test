#ifndef __MAIN_LEVEL_HPP
#define __MAIN_LEVEL_HPP

#include <godot_cpp/classes/node.hpp>

namespace godot {

class Node3D;

namespace framework {
class DataManager;
class SignalManager;
} // namespace framework

class MainLevel : public Node {
    GDCLASS(MainLevel, Node)

protected:
    static void _bind_methods();

public:
    MainLevel();
    ~MainLevel();

    void _ready() override;
    void _exit_tree() override;
};

} // namespace godot

#endif // __MAIN_LEVEL_HPP
