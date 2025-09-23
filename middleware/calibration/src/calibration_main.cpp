#include <windows.h>

#include <cstdio>

#include "calibration_shared_data.h"

using namespace middleware;

#define TAG "[Middleware-Calibration]"

int main(int argc, char* argv[]) {
    HANDLE map_file_handle = OpenFileMappingA(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        CALIBRATION_SHARED_DATA_NAME
    );

    if (map_file_handle == INVALID_HANDLE_VALUE) {
        printf(TAG"Open %s failed!\n", CALIBRATION_SHARED_DATA_NAME);
        return -1;
    }

    LPVOID p_shared_data_buffer = MapViewOfFile(
        map_file_handle,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        sizeof(CalibrationSharedData)
    );

    if (p_shared_data_buffer == nullptr) {
        printf(TAG"Point of %s is null!\n", CALIBRATION_SHARED_DATA_NAME);
        CloseHandle(map_file_handle);
        return -1;
    }

    CalibrationSharedData *p_calibration_shared_data = 
            reinterpret_cast<CalibrationSharedData *>(p_shared_data_buffer);

    printf(TAG"Main process command id: %u\n", p_calibration_shared_data->main_process_command.id);

    p_calibration_shared_data->sub_process_command.id = 1;
    p_calibration_shared_data->sub_process_command.type = 2;
    p_calibration_shared_data->sub_process_command.command = 3;

    UnmapViewOfFile(reinterpret_cast<LPVOID>(p_calibration_shared_data));
    CloseHandle(map_file_handle);

    Sleep(100);

    return 0;
}