#ifndef __CALIBRATION_LEVEL_HPP
#define __CALIBRATION_LEVEL_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

class Node3D;
class StandardMaterial3D;

namespace framework {
class DataManager;
class SignalManager;

struct ProcessData;
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
    framework::ProcessData *mp_process_data = nullptr;
};

} // namespace godot

#endif // __CALIBRATION_LEVEL_HPP
