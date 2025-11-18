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
    EStartMode start_mode{EStartMode::MAIN};

    ELevel next_level{ELevel::MAIN};
    ELevel current_level{ELevel::MAIN};

    int quit_code{0};
};

enum class EWindowMode : int8_t {
    WINDOWED = 0,
    FULLSCREEN_WINDOWED = 3,
    EXCLUSIVE_FULLSCREEN = 4,
};

struct UserConfigData {
    EWindowMode window_mode{EWindowMode::WINDOWED};
    float fov{45.0f};
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
    ECalibrationStatus calibration_status{ECalibrationStatus::IDLE};

    // Gyro
    int32_t gyro_raw_data[3]{};
    uint32_t gyro_sampling_count{0};
    uint32_t gyro_target_sampling_quantity{0};

    float gyro_static_square_error[4]{};
    float gyro_square_error[4]{};
    bool gyro_static_motion_flag{false};

    float gyro_optimizer_error{0.0f};

    // Acce
    int32_t acce_raw_data[3]{};
    uint32_t acce_sampling_count{0};
    uint32_t acce_target_sampling_quantity{0};

    float acce_static_square_error[4]{};
    float acce_square_error[4]{};
    bool acce_static_motion_flag{false};

    float acce_optimizer_error{0.0f};

    // Mag
    int16_t mag_raw_data[3]{};
    uint32_t mag_static_sampling_count{0};
    uint32_t mag_target_static_sampling_quantity{0};
    uint32_t mag_motion_sampling_count{0};
    uint32_t mag_target_motion_sampling_quantity{0};

    float mag_static_square_error[4]{};
    float mag_square_error[4]{};
    bool mag_static_motion_flag{false};

    float mag_optimizer_error{0.0f};

    // Progress
    float calibration_progress{0.0f};
};

} //namespace framework

} // namespace godot

#endif // __DATA_TYPE_H
