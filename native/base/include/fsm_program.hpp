#ifndef __FSM_PROGRAM_HPP
#define __FSM_PROGRAM_HPP

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/typed_dictionary.hpp>

#include "fsm_status.hpp"

namespace godot {

class FsmProgram final : public RefCounted {
    GDCLASS(FsmProgram, RefCounted)

protected:
    static void _bind_methods();

public:
    FsmProgram();
    ~FsmProgram();

private:
    TypedDictionary<int, FsmStatus> m_status_map;
    Ref<FsmContext> m_context;
    int m_current_status;
    Ref<FsmStatus> m_current_status_entity;

    void transfer_status(int next_status);

public:
    void set_context(Ref<FsmContext> &context);
    void register_status(
        int status,
        OnEnterAction on_enter_action,
        OnProcessAction on_process_action,
        OnExitAction on_exit_action,
        OnNextStatus on_next_status
    );
    void unregister_status(int status);
    void start(int status);
    void process();
};

} // namespace godot

#endif // __FSM_PROGRAM_HPP
