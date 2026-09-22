#ifndef BINARY_HPP
#define BINARY_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace Binary {
    std::string generate_cyclic_pattern(size_t length);
    size_t find_offset(const std::string& pattern, const std::string& crash_value);
    std::vector<uint8_t> generate_nop_sled(size_t length);
    
    // Shellcode encoding to remove null bytes
    std::vector<uint8_t> encode_shellcode(const std::vector<uint8_t>& shellcode, uint8_t xor_key);
    std::vector<uint8_t> decode_shellcode(const std::vector<uint8_t>& encoded, uint8_t xor_key);
}

#endif