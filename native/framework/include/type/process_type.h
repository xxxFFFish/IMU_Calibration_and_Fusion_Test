#ifndef __PROCESS_TYPE_H
#define __PROCESS_TYPE_H

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

#endif // __PROCESS_TYPE_H
