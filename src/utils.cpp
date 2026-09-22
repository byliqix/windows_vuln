#include "../include/utils.hpp"
#include <iomanip>
#include <sstream>

namespace Utils {
    void print_banner() {
        std::cout << CYAN << BOLD << "====================================================\n";
        std::cout << "   SECURITY ANALYSIS TOOLKIT - Binary & Crypto\n";
        std::cout << "   Developed for Advanced Security Research\n";
        std::cout << "====================================================" << RESET << "\n\n";
    }

    std::string string_to_hex(const std::string& input) {
        std::stringstream ss;
        for (unsigned char c : input) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
        }
        return ss.str();
    }

    std::string hex_to_string(const std::string& hex) {
        std::string result;
        for (size_t i = 0; i < hex.length(); i += 3) {
            if (i + 2 < hex.length()) {
                std::string byteString = hex.substr(i, 2);
                char byte = (char)strtol(byteString.c_str(), nullptr, 16);
                result += byte;
            }
        }
        return result;
    }
}