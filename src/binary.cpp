#include "../include/binary.hpp"
#include <sstream>
#include <algorithm>

namespace Binary {
    std::string generate_cyclic_pattern(size_t length) {
        std::string pattern = "";
        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < 256; ++j) {
                for (int k = 0; k < 256; ++k) {
                    pattern += (char)('A' + i);
                    pattern += (char)('A' + j);
                    pattern += (char)('A' + k);
                    if (pattern.length() >= length) {
                        return pattern.substr(0, length);
                    }
                }
            }
        }
        return pattern;
    }

    size_t find_offset(const std::string& pattern, const std::string& crash_value) {
        size_t pos = pattern.find(crash_value);
        if (pos == std::string::npos) return 0;
        return pos;
    }

    std::vector<uint8_t> generate_nop_sled(size_t length) {
        return std::vector<uint8_t>(length, 0x90);
    }

    std::vector<uint8_t> encode_shellcode(const std::vector<uint8_t>& shellcode, uint8_t xor_key) {
        std::vector<uint8_t> encoded = shellcode;
        for (auto& b : encoded) {
            b ^= xor_key;
        }
        return encoded;
    }

    std::vector<uint8_t> decode_shellcode(const std::vector<uint8_t>& encoded, uint8_t xor_key) {
        return encode_shellcode(encoded, xor_key); // XOR is symmetric
    }
}