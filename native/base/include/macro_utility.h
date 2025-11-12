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

#define GET_VARIANT_PROPERTY(name, var_type) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() == Variant::NIL) { \
        print_error(TAG#name" was not found!"); \
    } else if (var_##name.get_type() != Variant::var_type) { \
        print_error(TAG#name" type error!"); \
    } else { \
        m_##name = var_##name; \
    }

#define GET_RESOURCE_PROPERTY(name) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        m_##name = var_##name; \
        if (m_##name.is_null()) { \
            print_error(TAG#name" is null!"); \
        } \
    }

#define GET_PACKED_SCENE_PROPERTY(name, type_name) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        m_##name = var_##name; \
        if (unlikely(m_##name.is_null())) { \
            print_error(TAG#name" is null!"); \
        } else if (m_##name->get_state()->get_node_type(0) != type_name::get_class_static()) { \
            print_error(TAG#name" type error!"); \
        } \
    }

#define GET_NODE_PROPERTY(name, type_name) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        mp_##name = Object::cast_to<type_name>(var_##name); \
        if (mp_##name == nullptr) { \
            print_error(TAG#name" is null!"); \
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

#define CONNECT_NODE_PROPERTY_SIGNAL(name, signal_name, handler_name) \
    if (mp_##name == nullptr) { \
        print_error(TAG#name" is null!"); \
    } else { \
        if (mp_##name->connect(#signal_name, callable_mp(this, &handler_name)) != Error::OK) { \
            print_error(TAG"Connect "#name" signal "#signal_name" failed!"); \
        } \
    }

} // namespace godot

#endif // __MACRO_UTILITY_H
