#ifndef __MIDDLEWARE_MANAGER_HPP
#define __MIDDLEWARE_MANAGER_HPP

#include <godot_cpp/classes/node.hpp>

#include "type/middleware_type.h"

#include "calibration_shared_data.h"

namespace godot {

class Thread;

namespace framework {

class MiddlewareManager : public Node {
    GDCLASS(MiddlewareManager, Node)

private:
    struct CalibrationProcessHandle {
        String shared_data_name;
        size_t shared_data_size;
        void *p_file_mapping_handle{nullptr};
        void *p_shared_data_buffer{nullptr};

        uint16_t last_sub_process_command_id;
        bool wait_response_flag;
        unsigned int wait_response_counter;

        void *p_process_handle{nullptr};
        Ref<Thread> monitor_thread;

        bool is_running;
        unsigned int exit_wait_counter;
    };

    static MiddlewareManager *p_instance;

public:
    static MiddlewareManager *get_instance();

protected:
    static void _bind_methods();

public:
    MiddlewareManager();
    ~MiddlewareManager();

    void _ready() override;
    void _exit_tree() override;

private:
    // Properties
    String m_calibration_path;
    String m_fusion_path;

    bool m_enabled = false;

    CalibrationProcessHandle m_calibration_process_handle;

    String get_process_executable_file_path(EMiddleware object);

    // Calibration functions
    Error create_calibration_shared_data();
    void release_calibration_shared_data();

    void send_calibration_process_command(uint8_t type, uint8_t command);
    void send_calibration_response();

    void listen_calibration_sub_process_command();

    void calibration_sub_process_command_parser();
    void calibration_monitor_task();

    Error run_calibration();

public:
    void init();
    void deinit();

    Error run(EMiddleware object);
    void release(EMiddleware object);
    bool is_running(EMiddleware object);

    const middleware::CalibrationMonitorData *get_calibration_monitor_data();
    const middleware::CalibrationSamplingData *get_calibration_sampling_data();
    const middleware::CalibrationResultData *get_calibration_result_data();
};

} // namespace framework

} // namespace godot

#endif // __MIDDLEWARE_MANAGER_HPP
