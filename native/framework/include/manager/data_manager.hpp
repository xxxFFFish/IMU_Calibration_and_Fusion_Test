#ifndef __DATA_MANAGER_HPP
#define __DATA_MANAGER_HPP

#include <godot_cpp/classes/node.hpp>

#include "type/data_type.h"

namespace godot {

namespace framework {

class DataManager : public Node {
    GDCLASS(DataManager, Node)

private:
    static DataManager *p_instance;

public:
    static DataManager *get_instance();

protected:
    static void _bind_methods();

public:
    DataManager();
    ~DataManager();

    void _ready() override;
    void _exit_tree() override;

private:
    ProcessData m_process_data;
    UserConfigData m_user_config_data;

    CalibrationLevelData m_calibration_level_data;

public:
    void init();
    void deinit();

    const ProcessData *get_process_data() const { return &m_process_data; }
    ProcessData *own_process_data() { return &m_process_data; }

    const UserConfigData *get_user_config_data() const { return &m_user_config_data; }
    UserConfigData *own_user_config_data() { return &m_user_config_data; }

    const CalibrationLevelData *get_calibration_level_data() const { return &m_calibration_level_data; }
    CalibrationLevelData *own_calibration_level_data() { return &m_calibration_level_data; }
};

} // namespace framework

} // namespace godot

#endif // __DATA_MANAGER_HPP
