#ifndef __DATA_TYPE_H
#define __DATA_TYPE_H

#include <stdint.h>

namespace godot {

namespace framework {

enum class EStartMode : int32_t {
    MAIN,
    CALIBRATION,
    FUSION,
};

enum class ELevel : int32_t {
    MAIN,
    CALIBRATION,
    FUSION,
};

struct ProcessData {
    EStartMode start_mode;

    ELevel next_level;
    ELevel current_level;

    int quit_code;
};

enum class EWindowMode : int8_t {
    WINDOWED = 0,
    FULLSCREEN_WINDOWED = 3,
    EXCLUSIVE_FULLSCREEN = 4,
};

struct UserConfigData {
    EWindowMode window_mode;
    float fov;
};

} //namespace framework

} // namespace godot

#endif // __DATA_TYPE_H
