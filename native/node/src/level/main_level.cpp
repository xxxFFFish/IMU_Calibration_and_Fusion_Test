#include "level/main_level.hpp"

#include "manager/data_manager.hpp"
#include "manager/signal_manager.hpp"

using namespace godot;

#define TAG "[MainLevel]"

void MainLevel::_bind_methods() {}

MainLevel::MainLevel() {}

MainLevel::~MainLevel() {}

void MainLevel::_ready() {
    // Connect signal

    print_verbose(TAG"Ready.");
}

void MainLevel::_exit_tree() {
    // Disconnect signal

    print_verbose(TAG"Exit tree.");
}
