#ifndef __FSM_STATUS_HPP
#define __FSM_STATUS_HPP

#include <functional>

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

using OnEnterAction = std::function<void()>;
using OnProcessAction = std::function<void(double)>;
using OnExitAction = std::function<void()>;
using GetNextStatus = std::function<int()>;

class FsmStatus final : public RefCounted {
    GDCLASS(FsmStatus, RefCounted)

protected:
    static void _bind_methods() {}

public:
    FsmStatus() = default;
    ~FsmStatus() = default;

    OnEnterAction on_enter_action;
    OnProcessAction on_process_action;
    OnExitAction on_exit_action;
    GetNextStatus get_next_status;
};

} // namespace godot

#endif // __FSM_STATUS_HPP
