#ifndef __SIGNAL_TYPES_H
#define __SIGNAL_TYPES_H

namespace godot {

namespace framework {

#define CAST_TO_SIGNAL_NAME(signal) String::num_int64(static_cast<int64_t>(signal))

enum class ESignal : int64_t {
    PROCESS_QUIT,
    PROCESS_SWITCH_LEVEL,

    USER_CONFIG_SET_WINDOW_MODE,
    USER_CONFIG_SET_FOV,

    CURTAIN_CLOSE_FINISHED,
    CURTAIN_OPEN_FINISHED,
};

} //namespace framework

} // namespace godot

#endif // __SIGNAL_TYPES_H
