#include "manager/level_manager.hpp"

#include <godot_cpp/classes/scene_state.hpp>

#include "macro_utility.h"
#include "type/data_type.h"

#include "level/main_level.hpp"
#include "level/calibration_level.hpp"

using namespace godot;
using namespace framework;

#define TAG "[LevelManager]"

LevelManager *LevelManager::p_instance = nullptr;

LevelManager *LevelManager::get_instance() {
    RETURN_INSTANCE()
}

void LevelManager::_bind_methods() {}

LevelManager::LevelManager() {
    INIT_INSTANCE()
    print_verbose(TAG"Created.");
}

LevelManager::~LevelManager() {
    p_instance = nullptr;
}

void LevelManager::_ready() {
    // Check resource
    GET_PACKED_SCENE_PROPERTY(main_level_packed_scene, MainLevel)
    GET_PACKED_SCENE_PROPERTY(calibration_level_packed_scene, CalibrationLevel)

    print_verbose(TAG"Ready.");
}

void LevelManager::_exit_tree() {
    print_verbose(TAG"Exit tree.");
}

void LevelManager::init() {
    print_verbose(TAG"Init.");
}

void LevelManager::deinit() {
    print_verbose(TAG"Deinit.");
}

Node *LevelManager::instantiate_level(ELevel level) {
    Node *instance = nullptr;

    switch (level) {
        case ELevel::MAIN:
            if (likely(!m_main_level_packed_scene.is_null())) {
                instance = m_main_level_packed_scene->instantiate();
            }
            break;
        
        case ELevel::CALIBRATION:
            if (likely(!m_calibration_level_packed_scene.is_null())) {
                instance = m_calibration_level_packed_scene->instantiate();
            }
            break;

        default:;
    }

    return instance;
}
