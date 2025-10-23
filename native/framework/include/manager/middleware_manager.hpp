#ifndef __MIDDLEWARE_MANAGER_HPP
#define __MIDDLEWARE_MANAGER_HPP

#include <godot_cpp/classes/node.hpp>

#include "type/middleware_type.h"

namespace godot {

class Thread;

namespace framework {

class MiddlewareManager : public Node {
    GDCLASS(MiddlewareManager, Node)

private:
    struct ProcessHandle {
        EMiddleware type;

        String shared_data_name;
        size_t shared_data_size;
        void *p_map_file_handle{nullptr};
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

    ProcessHandle m_calibration_process_handle;
    ProcessHandle m_fusion_process_handle;

    String get_process_executable_file_path(EMiddleware object);

    Error create_shared_data(ProcessHandle *p_process_handle);
    void release_shared_data(ProcessHandle *p_process_handle);

    void init_shared_data_process_command(ProcessHandle *p_process_handle);
    void send_shared_data_process_command(ProcessHandle *p_process_handle, uint8_t type, uint8_t command);
    void send_response(ProcessHandle *p_process_handle);

    void listen_sub_process_command(ProcessHandle *p_process_handle);

    void calibration_sub_process_command_parser();
    void calibration_monitor_task();

    void fusion_sub_process_command_parser();
    void fusion_monitor_task();

public:
    void init();
    void deinit();

    Error run(EMiddleware object);
    void stop(EMiddleware object);
    bool is_running(EMiddleware object);
};

} // namespace framework

} // namespace godot

#endif // __MIDDLEWARE_MANAGER_HPP
