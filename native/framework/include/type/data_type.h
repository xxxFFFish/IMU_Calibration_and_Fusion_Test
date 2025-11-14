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

enum class ECalibrationStatus : int8_t {
    ERROR = -1,
    IDLE,
    PRE_SAMPLING,
    PRE_SAMPLING_END,
    MOTION_SAMPLING,
    STATIC_SAMPLING,
    STATIC_SAMPLING_END,
    SAMPLING_END,
    AWAIT_RESULT,
    CALIBRATION_END,
};

struct CalibrationLevelData {
    ECalibrationStatus calibration_status;

    // Gyro
    int32_t gyro_raw_data[3];
    uint32_t gyro_sampling_count;
    uint32_t gyro_target_sampling_quantity;

    float gyro_static_square_error[4];
    float gyro_square_error[4];
    bool gyro_static_motion_flag;

    float gyro_optimizer_error;

    // Acce
    int32_t acce_raw_data[3];
    uint32_t acce_sampling_count;
    uint32_t acce_target_sampling_quantity;

    float acce_static_square_error[4];
    float acce_square_error[4];
    bool acce_static_motion_flag;

    float acce_optimizer_error;

    // Mag
    int16_t mag_raw_data[3];
    uint32_t mag_static_sampling_count;
    uint32_t mag_target_static_sampling_quantity;
    uint32_t mag_motion_sampling_count;
    uint32_t mag_target_motion_sampling_quantity;

    float mag_static_square_error[4];
    float mag_square_error[4];
    bool mag_static_motion_flag;

    float mag_optimizer_error;

    // Progress
    float calibration_progress;
};

} //namespace framework

} // namespace godot

#endif // __DATA_TYPE_H
