#ifndef __CALIBRATION_SHARED_DATA_H
#define __CALIBRATION_SHARED_DATA_H

#include "process_command.h"

#define CALIBRATION_SHARED_DATA_NAME "CalibrationSharedData"

namespace middleware {

#pragma pack(push, 1)
struct CalibrationSharedData {
    ProcessCommand main_process_command;
    ProcessCommand sub_process_command;
};
#pragma pack(pop)

} //namespace middleware

#endif // __CALIBRATION_SHARED_DATA_H
