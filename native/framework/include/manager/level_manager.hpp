#ifndef __LEVEL_MANAGER_HPP
#define __LEVEL_MANAGER_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

namespace framework {

enum class ELevel;

class LevelManager : public Node {
    GDCLASS(LevelManager, Node)

private:
    static LevelManager *p_instance;

public:
    static LevelManager *get_instance();

protected:
    static void _bind_methods();

public:
    LevelManager();
    ~LevelManager();

    void _ready() override;
    void _exit_tree() override;

private:
    // Properties
    Ref<PackedScene> m_main_level_packed_scene;

public:
    void init();
    void deinit();

    Node *instantiate_level(ELevel level);
};

} // namespace framework

} // namespace godot

#endif // __LEVEL_MANAGER_HPP
