#ifndef SYS_INTERACT_HPP
#define SYS_INTERACT_HPP

#include <windows.h>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

namespace SysInteract {
    // Membaca memory dari proses lain berdasarkan address
    bool read_process_memory(DWORD process_id, uintptr_t address, std::vector<uint8_t>& buffer, size_t size);
    
    // Mengirim IOCTL ke Driver (untuk riset kernel/HEVD)
    bool send_ioctl(const std::string& device_name, DWORD ioctl_code, void* input_buffer, size_t input_size, void* output_buffer, size_t output_size);
}

#endif