#ifndef __MACRO_UTILITY_H
#define __MACRO_UTILITY_H

namespace godot {

#define INIT_INSTANCE() \
    if (p_instance == nullptr) { \
        p_instance = this; \
    } else { \
        print_error(TAG"Instance was created!"); \
    }

#define RETURN_INSTANCE() \
    if (p_instance == nullptr) { \
        print_error(TAG"Instance is empty!"); \
    } \
    return p_instance;

#define INIT_MANAGER(name, type_name) \
    if (mp_##name##_manager) { \
        mp_##name##_manager->init(); \
    } else { \
        print_error(TAG#type_name" instance is null!"); \
    }

#define DEINIT_MANAGER(name) \
    if (mp_##name##_manager) { \
        mp_##name##_manager->deinit(); \
    }

#define ENABLE_FLAG() \
    if (m_enabled) { \
        print_line(TAG"It is already initialized!"); \
        return; \
    } \
    m_enabled = true;

#define DISABLE_FLAG() \
    if (!m_enabled) { \
        print_line(TAG"It dose not need to be deinitialized!"); \
        return; \
    } \
    m_enabled = false;

#define GET_RESOURCE_PROPERTY(name, var_name) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        var_name = var_##name; \
        if (var_name.is_null()) { \
            print_error(TAG#name" is null!"); \
        } \
    }

#define GET_PACKED_SCENE_PROPERTY(name, var_name, type_name) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        var_name = var_##name; \
        if (unlikely(var_name.is_null())) { \
            print_error(TAG#name" is null!"); \
        } else if (var_name->get_state()->get_node_type(0) != type_name::get_class_static()) { \
            print_error(TAG#name" type error!"); \
        } \
    }

#define GET_NODE_PROPERTY(name, var_name, type_name) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        var_name = Object::cast_to<type_name>(var_##name); \
        if (var_name == nullptr) { \
            print_error(TAG#name" is null!"); \
        } \
    }

#define GET_AND_INIT_LABEL_PROPERTY(name, var_name, label_key) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        var_name = Object::cast_to<Label>(var_##name); \
        if (unlikely(var_name == nullptr)) { \
            print_error(TAG#name" is null!"); \
        } else {\
            var_name->set_text( \
                framework::TextManager::get_instance()->get_gui_text_key( \
                    framework::EGuiText::label_key \
                ) \
            ); \
        } \
    }

#define GET_AND_INIT_BUTTON_PROPERTY(name, var_name, label_key, pressed_handler_name) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        var_name = Object::cast_to<Button>(var_##name); \
        if (unlikely(var_name == nullptr)) { \
            print_error(TAG#name" is null!"); \
        } else {\
            var_name->set_text( \
                framework::TextManager::get_instance()->get_gui_text_key( \
                    framework::EGuiText::label_key \
                ) \
            ); \
            if (var_name->connect( \
                "pressed", callable_mp(this, &pressed_handler_name)) != Error::OK) { \
                print_error(TAG"Connect "#name" signal pressed failed!"); \
            } \
        } \
    }

#define CONNECT_FRAMEWORK_SIGNAL(name, handler_name) \
    if (framework::SignalManager::get_instance()->signal_connect( \
        framework::ESignal::name, \
        callable_mp(this, &handler_name) \
    ) != Error::OK) { \
        print_error(TAG"Connect signal "#name" failed!"); \
    }

#define DISCONNECT_FRAMEWORK_SIGNAL(name, handler_name) \
    framework::SignalManager::get_instance()->signal_disconnect( \
        framework::ESignal::name, \
        callable_mp(this, &handler_name) \
    );

} // namespace godot

#endif // __MACRO_UTILITY_H
