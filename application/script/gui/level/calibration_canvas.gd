extends CalibrationCanvas

@export var status_label : Label
@export var status_color_rect : ColorRect

@export var gyro_x_data_label : Label
@export var gyro_y_data_label : Label
@export var gyro_z_data_label : Label
@export var gyro_count_label : Label

@export var acce_x_data_label : Label
@export var acce_y_data_label : Label
@export var acce_z_data_label : Label
@export var acce_count_label : Label

@export var mag_x_data_label : Label
@export var mag_y_data_label : Label
@export var mag_z_data_label : Label
@export var mag_static_count_label : Label
@export var mag_motion_count_label : Label

@export var gyro_motion_flag_color_rect : ColorRect
@export var gyro_x_square_error_label : Label
@export var gyro_y_square_error_label : Label
@export var gyro_z_square_error_label : Label
@export var gyro_sum_square_error_label : Label
@export var gyro_x_static_square_error_label : Label
@export var gyro_y_static_square_error_label : Label
@export var gyro_z_static_square_error_label : Label
@export var gyro_sum_static_square_error_label : Label

@export var acce_motion_flag_color_rect : ColorRect
@export var acce_x_square_error_label : Label
@export var acce_y_square_error_label : Label
@export var acce_z_square_error_label : Label
@export var acce_sum_square_error_label : Label
@export var acce_x_static_square_error_label : Label
@export var acce_y_static_square_error_label : Label
@export var acce_z_static_square_error_label : Label
@export var acce_sum_static_square_error_label : Label

@export var mag_motion_flag_color_rect : ColorRect
@export var mag_x_square_error_label : Label
@export var mag_y_square_error_label : Label
@export var mag_z_square_error_label : Label
@export var mag_sum_square_error_label : Label
@export var mag_x_static_square_error_label : Label
@export var mag_y_static_square_error_label : Label
@export var mag_z_static_square_error_label : Label
@export var mag_sum_static_square_error_label : Label

@export var calibration_progress_bar : ProgressBar

@export var sampling_flag_color : Color
@export var waiting_flag_color : Color

@export var motion_flag_color : Color
@export var static_flag_color : Color

@export var hint_panel_container : PanelContainer
@export var hint_label : Label
@export var enter_button : Button
