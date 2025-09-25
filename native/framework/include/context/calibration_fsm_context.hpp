#ifndef __CALIBRATION_FSM_CONTEXT_HPP
#define __CALIBRATION_FSM_CONTEXT_HPP

#include "fsm_context.hpp"

namespace godot {

namespace framework {

class CalibrationFsmContext : public FsmContext {
    GDCLASS(CalibrationFsmContext, FsmContext)

public:
    enum class ECalibrationFsmStatus : int {
        ERROR = -1,
        IDLE = 0,
        PRE_SAMPLING,
        PRE_SAMPLING_END,
    };

protected:
    static void _bind_methods();

public:
    CalibrationFsmContext();
    ~CalibrationFsmContext();
};

} // namespace framework

} // namespace godot

#endif // __CALIBRATION_FSM_CONTEXT_HPP
