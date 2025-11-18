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
