#include "manager/data_manager.hpp"

#include "macro_utility.h"

using namespace godot;
using namespace framework;

#define TAG "[DataManager]"

DataManager *DataManager::p_instance = nullptr;

DataManager *DataManager::get_instance() {
    RETURN_INSTANCE()
}

void DataManager::_bind_methods() {}

DataManager::DataManager() {
    INIT_INSTANCE()

    m_process_data.start_mode = EStartMode::MAIN;
    m_process_data.next_level = ELevel::MAIN;
    m_process_data.current_level = ELevel::MAIN;
    m_process_data.quit_code = 0;

    m_user_config_data.window_mode = EWindowMode::WINDOWED;
    m_user_config_data.fov = 45.0f;

    print_verbose(TAG"Created.");
}

DataManager::~DataManager() {
    p_instance = nullptr;
}

void DataManager::_ready() {
    print_verbose(TAG"Ready.");
}

void DataManager::_exit_tree() {
    print_verbose(TAG"Exit tree.");
}

void DataManager::init() {
    print_verbose(TAG"Init.");
}

void DataManager::deinit() {
    print_verbose(TAG"Deinit.");
}
