#ifndef __USER_CONFIG_TYPE_H
#define __USER_CONFIG_TYPE_H

#include <stdint.h>

namespace godot {

namespace framework {

enum class EWindowMode : int8_t {
    WINDOWED = 0,
    FULLSCREEN_WINDOWED = 3,
    EXCLUSIVE_FULLSCREEN = 4,
};

} //namespace framework

} // namespace godot

#endif // __USER_CONFIG_TYPE_H
