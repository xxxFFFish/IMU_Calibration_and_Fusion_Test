#include "manager/text_manager.hpp"

#include "macro_utility.h"

using namespace godot;
using namespace framework;

#define TAG "[TextManager]"

TextManager *TextManager::p_instance = nullptr;

TextManager *TextManager::get_instance() {
    RETURN_INSTANCE()
}

void TextManager::_bind_methods() {}

TextManager::TextManager() {
    INIT_INSTANCE()
    print_verbose(TAG"Created.");
}

TextManager::~TextManager() {
    p_instance = nullptr;
}

void TextManager::_ready() {
    print_verbose(TAG"Ready.");
}

void TextManager::_exit_tree() {
    print_verbose(TAG"Exit tree.");
}

void TextManager::init() {
    ENABLE_FLAG()
    print_verbose(TAG"Init.");
}

void TextManager::deinit() {
    DISABLE_FLAG()
    print_verbose(TAG"Deinit.");
}

const char *TextManager::get_gui_text_key(EGuiText gui_text) {
    switch (gui_text) {
        #define _ENUM_CASE(name) case EGuiText::name: return #name;
        GUI_TEXT_ENUM(_ENUM_CASE)
        #undef _ENUM_CASE

        default:
            return "";
    }
}
