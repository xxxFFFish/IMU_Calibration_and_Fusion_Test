#include "manager/chief_manager.hpp"

#include "macro_utility.h"

#include "manager/data_manager.hpp"
#include "manager/text_manager.hpp"
#include "manager/signal_manager.hpp"
#include "manager/level_manager.hpp"
#include "manager/gui_manager.hpp"
#include "manager/middleware_manager.hpp"

using namespace godot;
using namespace framework;

#define TAG "[ChiefManager]"

ChiefManager *ChiefManager::p_instance = nullptr;

ChiefManager *ChiefManager::get_instance() {
    RETURN_INSTANCE()
}

void ChiefManager::_bind_methods() {}

ChiefManager::ChiefManager() {
    INIT_INSTANCE()
    print_verbose(TAG"Created.");
}

ChiefManager::~ChiefManager() {
    p_instance = nullptr;
}

void ChiefManager::_ready() {
    mp_data_manager = DataManager::get_instance();
    mp_text_manager = TextManager::get_instance();
    mp_signal_manager = SignalManager::get_instance();
    mp_level_manager = LevelManager::get_instance();
    mp_gui_manager = GuiManager::get_instance();
    mp_middleware_manager = MiddlewareManager::get_instance();

    print_verbose(TAG"Ready.");
}

void ChiefManager::_exit_tree() {
    print_verbose(TAG"Exit tree.");
}

void ChiefManager::init() {
    INIT_MANAGER(data, DataManager)
    INIT_MANAGER(text, TextManager)
    INIT_MANAGER(signal, SignalManager)
    INIT_MANAGER(level, LevelManager)
    INIT_MANAGER(gui, GuiManager)
    INIT_MANAGER(middleware, MiddlewareManager)

    print_verbose(TAG"Init.");
}

void ChiefManager::deinit() {
    DEINIT_MANAGER(middleware)
    DEINIT_MANAGER(gui)
    DEINIT_MANAGER(level)
    DEINIT_MANAGER(signal)
    DEINIT_MANAGER(text)
    DEINIT_MANAGER(data)

    print_verbose(TAG"Deinit.");
}
