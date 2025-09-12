#include "main/main.hpp"

#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/translation_server.hpp>
#include <godot_cpp/classes/scene_state.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>

using namespace godot;

#define TAG "[Main]"

void Main::_bind_methods() {
    
}

Main::Main() {}

Main::~Main() {}

void Main::_ready() {
    print_verbose(TAG"Ready begin.");

    // Check and initilize resource

    // Initilize framework autoload node

    // Get data point

    // Connect framework signal

    print_verbose(TAG"Ready end.");
}

void Main::_exit_tree() {
    print_verbose(TAG"Exit tree begin.");

    // Disconnect framework signal

    print_verbose(TAG"Exit tree end.");
}
