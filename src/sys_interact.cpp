#include "../include/sys_interact.hpp"
#include <cstdint>
#include <psapi.h>

namespace SysInteract {
    bool read_process_memory(DWORD process_id, uintptr_t address, std::vector<uint8_t>& buffer, size_t size) {
        HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, process_id);
        if (hProcess == NULL) {
            std::cerr << "Error: Could not open process. Try running as Administrator.\n";
            return false;
        }

        buffer.resize(size);
        SIZE_T bytesRead;
        if (ReadProcessMemory(hProcess, (LPCVOID)address, buffer.data(), size, &bytesRead)) {
            CloseHandle(hProcess);
            return true;
        }

        CloseHandle(hProcess);
        return false;
    }

    bool send_ioctl(const std::string& device_name, DWORD ioctl_code, void* input_buffer, size_t input_size, void* output_buffer, size_t output_size) {
        HANDLE hDevice = CreateFileA(device_name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hDevice == INVALID_HANDLE_VALUE) {
            std::cerr << "Error: Could not open device driver. Check if HEVD is installed.\n";
            return false;
        }

        DWORD bytesReturned;
        BOOL success = DeviceIoControl(hDevice, ioctl_code, input_buffer, (DWORD)input_size, output_buffer, (DWORD)output_size, &bytesReturned, NULL);
        
        CloseHandle(hDevice);
        return success;
    }
}