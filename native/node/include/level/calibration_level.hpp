#ifndef __CALIBRATION_LEVEL_HPP
#define __CALIBRATION_LEVEL_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

class Node3D;
class StandardMaterial3D;

class FsmProgram;

namespace framework {
struct ProcessData;
struct CalibrationLevelData;
} // namespace framework

namespace middleware {
struct CalibrationMonitorData;
struct CalibrationSamplingData;
struct CalibrationResultData;
} // namespace middleware

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
    framework::ProcessData *mp_process_data = nullptr;
    framework::CalibrationLevelData *mp_calibration_level_data = nullptr;

    Ref<FsmProgram> m_fsm_program;

    // Shared data
    const middleware::CalibrationMonitorData *mp_calibration_monitor_data = nullptr;
    const middleware::CalibrationSamplingData *mp_calibration_sampling_data = nullptr;
    const middleware::CalibrationResultData *mp_calibration_result_data = nullptr;

    void register_fsm_status();
};

} // namespace godot

#endif // __CALIBRATION_LEVEL_HPP
