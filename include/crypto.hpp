#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>
#include <vector>

namespace Crypto {
    std::string xor_cipher(const std::string& data, const std::string& key);
    double calculate_entropy(const std::string& data);
}

#endif