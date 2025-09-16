#ifndef __PROCESS_TYPES_H
#define __PROCESS_TYPES_H

#include <stdint.h>

namespace godot {

namespace framework {

enum class EStartMode : int32_t {
    MAIN,
    CALIBRATION,
    FUSION,
};

} //namespace framework

} // namespace godot

#endif // __PROCESS_TYPES_H
