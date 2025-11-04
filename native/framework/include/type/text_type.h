#ifndef __TEXT_TYPE_H
#define __TEXT_TYPE_H

#include <stdint.h>

namespace godot {

namespace framework {

#define GUI_TEXT_ENUM(X) \
    X(UNIVERSAL_LABEL_GYRO) \
    X(UNIVERSAL_LABEL_ACCELEROMETER) \
    X(UNIVERSAL_LABEL_MAGNETOMETER)


#define _ENUM_BUILD(name) name,
enum class EGuiText : int32_t { GUI_TEXT_ENUM(_ENUM_BUILD) };
#undef _ENUM_BUILD

} //namespace framework

} // namespace godot

#endif // __TEXT_TYPE_H
