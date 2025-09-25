#ifndef __FSM_STATUS_HPP
#define __FSM_STATUS_HPP

#include "fsm_context.hpp"

namespace godot {

using OnEnterAction = void(*)(Ref<FsmContext> &context);
using OnProcessAction = void(*)(Ref<FsmContext> &context);
using OnExitAction = void(*)(Ref<FsmContext> &context);
using OnNextStatus = int(*)(Ref<FsmContext> &context);

class FsmStatus : public RefCounted {
    GDCLASS(FsmStatus, RefCounted)

protected:
    static void _bind_methods() {}

public:
    FsmStatus() = default;
    ~FsmStatus() = default;

    OnEnterAction on_enter_action;
    OnProcessAction on_process_action;
    OnExitAction on_exit_action;
    OnNextStatus on_next_status;
};

} // namespace godot

#endif // __FSM_STATUS_HPP
