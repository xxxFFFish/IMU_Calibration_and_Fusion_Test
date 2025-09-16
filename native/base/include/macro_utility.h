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

#define GET_PACKED_SCENE_PROPERTY(name, var_name, type_name) \
    Variant var_##name = this->get(#name); \
    if (var_##name.get_type() != Variant::OBJECT) { \
        print_error(TAG#name" was not found!"); \
    } else { \
        var_name = var_##name; \
        if (var_name->get_state()->get_node_type(0) != type_name::get_class_static()) { \
            print_error(TAG#name" type error!"); \
        } \
    }

} // namespace godot

#endif // __MACRO_UTILITY_H
