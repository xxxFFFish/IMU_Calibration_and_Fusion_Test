#ifndef __FSM_CONTEXT_HPP
#define __FSM_CONTEXT_HPP

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class FsmContext : public RefCounted {
    GDCLASS(FsmContext, RefCounted)

protected:
    static void _bind_methods() {}

    FsmContext() = default;
    virtual ~FsmContext() = default;
};

} // namespace godot

#endif // __FSM_CONTEXT_HPP
