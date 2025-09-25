#include "fsm_program.hpp"

using namespace godot;

#define TAG "[FsmProgram]"

void FsmProgram::_bind_methods() {}

FsmProgram::FsmProgram() {}

FsmProgram::~FsmProgram() {}

void FsmProgram::transfer_status(int next_status) {
    if (next_status == m_current_status) {
        return;
    }

    if (!m_status_map.has(next_status)) {
        print_error(vformat(TAG"Attempt to transfer to invalid status: %d!", next_status));
        next_status = m_current_status;
        return;
    }

    Ref<FsmStatus> next_status_entity = m_status_map[next_status];

    if (m_current_status_entity->on_exit_action != nullptr) {
        m_current_status_entity->on_exit_action(m_context);
    }

    if (next_status_entity->on_enter_action != nullptr) {
        next_status_entity->on_enter_action(m_context);
    }

    m_current_status = next_status;
    m_current_status_entity = next_status_entity;
}

void FsmProgram::set_context(Ref<FsmContext> &context) {
    if (context.is_null()) {
        print_error(TAG"Context is null!");
        return;
    }

    m_context = context;
}

void FsmProgram::register_status(
        int status,
        OnEnterAction on_enter_action,
        OnProcessAction on_process_action,
        OnExitAction on_exit_action,
        OnNextStatus on_next_status
    ) {
    Ref<FsmStatus> status_entity;
    status_entity.instantiate();
    status_entity->on_enter_action = on_enter_action;
    status_entity->on_process_action = on_process_action;
    status_entity->on_exit_action = on_exit_action;
    status_entity->on_next_status = on_next_status;

    m_status_map[status] = status_entity;
}

void FsmProgram::unregister_status(int status) {
    m_status_map.erase(status);
}

void FsmProgram::start(int status) {
    if (!m_status_map.has(status)) {
        print_error(vformat(TAG"Attempt to start invalid status: %d!", status));
        return;
    }

    Ref<FsmStatus> status_entity = m_status_map[status];

    if (status_entity->on_enter_action != nullptr) {
        status_entity->on_enter_action(m_context);
    }

    m_current_status = status;
    m_current_status_entity = status_entity;
}

void FsmProgram::process() {
    if (m_current_status_entity->on_process_action != nullptr) {
        m_current_status_entity->on_process_action(m_context);
    }

    if (m_current_status_entity->on_next_status != nullptr) {
        transfer_status(m_current_status_entity->on_next_status(m_context));
    }
}
