#ifndef __CALIBRATION_LEVEL_HPP
#define __CALIBRATION_LEVEL_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace middleware {
struct CalibrationMonitorData;
struct CalibrationSamplingData;
struct CalibrationResultData;
} // namespace middleware

namespace godot {

class CalibrationCanvas;

class FsmProgram;

namespace framework {
struct ProcessData;
struct CalibrationLevelData;
} // namespace framework

class CalibrationLevel : public Node {
    GDCLASS(CalibrationLevel, Node)

protected:
    static void _bind_methods();

public:
    CalibrationLevel();
    ~CalibrationLevel();

    void _ready() override;
    void _exit_tree() override;
    void _process(double delta) override;

private:
    // Properties
    CalibrationCanvas *mp_calibration_canvas = nullptr;

    framework::ProcessData *mp_process_data = nullptr;
    framework::CalibrationLevelData *mp_calibration_level_data = nullptr;

    Ref<FsmProgram> m_fsm_program;

    bool m_hint_enter_flag = false;

    // Shared data
    const middleware::CalibrationMonitorData *mp_calibration_monitor_data = nullptr;
    const middleware::CalibrationSamplingData *mp_calibration_sampling_data = nullptr;
    const middleware::CalibrationResultData *mp_calibration_result_data = nullptr;

    void register_fsm_status();

    void transfer_gyro_data();
    void transfer_gyro_square_error();
    void transfer_acce_data();
    void transfer_acce_square_error();
    void transfer_mag_data();
    void transfer_mag_square_error();
    void calculate_calibration_progress();

    // Signal handlers
    void on_calibration_hint_enter();
};

} // namespace godot

#endif // __CALIBRATION_LEVEL_HPP
