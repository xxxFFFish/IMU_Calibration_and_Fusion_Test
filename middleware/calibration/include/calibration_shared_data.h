#ifndef __CALIBRATION_SHARED_DATA_H
#define __CALIBRATION_SHARED_DATA_H

#include <stdint.h>

#define CALIBRATION_SHARED_DATA_NAME "CalibrationSharedData"
#define CALIBRATION_GYRO_TARGET_SAMPLING_QUANTITY (24)
#define CALIBRATION_ACCE_TARGET_SAMPLING_QUANTITY (24)
#define CALIBRATION_MAG_TARGET_STATIC_SAMPLING_QUANTITY (24)
#define CALIBRATION_MAG_MAX_MOTION_SAMPLING_QUANTITY (2400)

namespace middleware {
enum class EProcessCommandType : uint8_t {
    EXIT = 0,
    RESPONSE,
};

#pragma pack(push, 1)
struct CalibrationProcessCommand {
    uint16_t id{0};
    uint8_t type{0};
    uint8_t command{0};
};

struct CalibrationMonitorData {
    // Gyro
    int32_t gyro_raw_data[3];
    uint32_t gyro_sampling_count;

    double gyro_static_square_error[4];
    double gyro_square_error[4];
    int32_t gyro_static_motion_flag;

    double gyro_optimizer_error;

    // Acce
    int32_t acce_raw_data[3];
    uint32_t acce_sampling_count;

    double acce_static_square_error[4];
    double acce_square_error[4];
    int32_t acce_static_motion_flag;

    double acce_optimizer_error;

    // Mag
    int16_t mag_raw_data[3];
    uint32_t mag_static_sampling_count;
    uint32_t mag_motion_sampling_count;

    double mag_static_square_error[4];
    double mag_square_error[4];
    int32_t mag_static_motion_flag;

    uint32_t mag_motion_sampling_filter_count;
    double mag_optimizer_error;
};

struct CalibrationSamplingData {
    uint32_t gyro_target_sampling_quantity;
    double gyro_sampling_buffer[CALIBRATION_GYRO_TARGET_SAMPLING_QUANTITY][3];

    uint32_t acce_target_sampling_quantity;
    double acce_sampling_buffer[CALIBRATION_ACCE_TARGET_SAMPLING_QUANTITY][3];

    uint32_t mag_target_static_sampling_quantity;
    double mag_static_sampling_buffer[CALIBRATION_MAG_TARGET_STATIC_SAMPLING_QUANTITY][3];

    uint32_t mag_target_motion_sampling_quantity;
    int16_t mag_motion_sampling_buffer[CALIBRATION_MAG_MAX_MOTION_SAMPLING_QUANTITY][3];
};

struct CalibrationResultData {
    float gyro_bias[3];
    float gyro_axis_matrix[9];
    float gyro_rotation_matrix[9];
    
    float acce_bias[3];
    float acce_axis_matrix[9];
    float acce_rotation_matrix[9];

    float mag_bias[3];
    float mag_axis_matrix[9];
    float mag_rotation_matrix[9];
};

struct CalibrationSharedData {
    CalibrationProcessCommand main_process_command;
    CalibrationProcessCommand sub_process_command;
    CalibrationMonitorData monitor_data;
    CalibrationSamplingData sampling_data;
    CalibrationResultData result_data;
};
#pragma pack(pop)

} //namespace middleware

#endif // __CALIBRATION_SHARED_DATA_H
