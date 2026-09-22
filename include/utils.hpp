#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <iostream>

namespace Utils {
    // ANSI Colors for "hacker" aesthetic
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string BOLD = "\033[1m";

    void print_banner();
    std::string hex_to_string(const std::string& hex);
    std::string string_to_hex(const std::string& input);
}

#endif