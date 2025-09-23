#ifndef __DATA_TYPE_H
#define __DATA_TYPE_H

#include "type/process_type.h"
#include "type/user_config_type.h"
#include "type/level_type.h"

namespace godot {

namespace framework {

struct ProcessData {
    EStartMode start_mode;

    ELevel next_level;
    ELevel current_level;

    int quit_code;
};

struct UserConfigData {
    EWindowMode window_mode;
    float fov;
};

} //namespace framework

} // namespace godot

#endif // __DATA_TYPE_H
