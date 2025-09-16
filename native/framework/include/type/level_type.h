#ifndef __LEVEL_TYPES_H
#define __LEVEL_TYPES_H

#include <stdint.h>

namespace godot {

namespace framework {

enum class ELevel : int32_t {
    MAIN,
    CALIBRATION,
    FUSION,
};

} //namespace framework

} // namespace godot

#endif // __LEVEL_TYPES_H
