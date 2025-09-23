#ifndef __SIGNAL_MANAGER_HPP
#define __SIGNAL_MANAGER_HPP

#include <godot_cpp/classes/node.hpp>

#include "type/signal_type.h"

namespace godot {

namespace framework {

class SignalManager : public Node {
    GDCLASS(SignalManager, Node)

private:
    static SignalManager *p_instance;

public:
    static SignalManager *get_instance();

protected:
    static void _bind_methods();

public:
    SignalManager();
    ~SignalManager();

    void _ready() override;
    void _exit_tree() override;

private:
    bool m_enabled = false;

public:
    void init();
    void deinit();

    Error signal_connect(ESignal signal, const Callable &p_callable);
    void signal_disconnect(ESignal signal, const Callable &p_callable);

    Error signal_emit(ESignal signal);
    void signal_emit_deferred(ESignal signal);
};

} // namespace framework

} // namespace godot

#endif // __SIGNAL_MANAGER_HPP
