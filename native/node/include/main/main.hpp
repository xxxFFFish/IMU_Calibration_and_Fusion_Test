#ifndef __MAIN_HPP
#define __MAIN_HPP

#include <godot_cpp/classes/node.hpp>

namespace godot {

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

// Private Properties
private:

// Pirvate Members
private:

};

} // namespace godot

#endif // __MAIN_HPP
