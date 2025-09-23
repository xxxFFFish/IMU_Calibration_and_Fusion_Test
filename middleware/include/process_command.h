#ifndef __PROCESS_COMMAND_H
#define __PROCESS_COMMAND_H

#include <stdint.h>

namespace middleware {

#pragma pack(push, 1)
struct ProcessCommand {
    uint16_t id{0};
    uint8_t type{0};
    uint8_t command{0};
};
#pragma pack(pop)

enum class EProcessCommandType : uint8_t {
    EXIT = 0,
};

} //namespace middleware

#endif // __PROCESS_COMMAND_H
