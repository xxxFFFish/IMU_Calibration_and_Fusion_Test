#include "manager/signal_manager.hpp"

#include "macro_utility.h"

using namespace godot;
using namespace framework;

#define TAG "[SignalManager]"

SignalManager *SignalManager::p_instance = nullptr;

SignalManager *SignalManager::get_instance() {
    RETURN_INSTANCE()
}

void SignalManager::_bind_methods() {
    ADD_SIGNAL(MethodInfo(CAST_TO_SIGNAL_NAME(ESignal::PROCESS_QUIT)));
    ADD_SIGNAL(MethodInfo(CAST_TO_SIGNAL_NAME(ESignal::PROCESS_SWITCH_LEVEL)));

    ADD_SIGNAL(MethodInfo(CAST_TO_SIGNAL_NAME(ESignal::USER_CONFIG_SET_WINDOW_MODE)));
    ADD_SIGNAL(MethodInfo(CAST_TO_SIGNAL_NAME(ESignal::USER_CONFIG_SET_FOV)));

    ADD_SIGNAL(MethodInfo(CAST_TO_SIGNAL_NAME(ESignal::CURTAIN_CLOSE_FINISHED)));
    ADD_SIGNAL(MethodInfo(CAST_TO_SIGNAL_NAME(ESignal::CURTAIN_OPEN_FINISHED)));

    ADD_SIGNAL(MethodInfo(CAST_TO_SIGNAL_NAME(ESignal::CALIBRATION_NONE_RESPONSE)));
    ADD_SIGNAL(MethodInfo(CAST_TO_SIGNAL_NAME(ESignal::CALIBRATION_HINT_ENTER)));
}

SignalManager::SignalManager() {
    INIT_INSTANCE()
    print_verbose(TAG"Created.");
}

SignalManager::~SignalManager() {
    p_instance = nullptr;
}

void SignalManager::_ready() {
    print_verbose(TAG"Ready.");
}

void SignalManager::_exit_tree() {
    print_verbose(TAG"Exit tree.");
}

void SignalManager::init() {
    ENABLE_FLAG()
    print_verbose(TAG"Init.");
}

void SignalManager::deinit() {
    DISABLE_FLAG()
    print_verbose(TAG"Deinit.");
}

Error SignalManager::signal_connect(ESignal signal, const Callable &p_callable) {
    return this->connect(CAST_TO_SIGNAL_NAME(signal), p_callable);
}

void SignalManager::signal_disconnect(ESignal signal, const Callable &p_callable) {
    this->disconnect(CAST_TO_SIGNAL_NAME(signal), p_callable);
}

Error SignalManager::signal_emit(ESignal signal) {
    return this->emit_signal(CAST_TO_SIGNAL_NAME(signal));
}

void SignalManager::signal_emit_deferred(ESignal signal) {
    if (!m_enabled) {
        return;
    }

    this->call_deferred("emit_signal", CAST_TO_SIGNAL_NAME(signal));
}
