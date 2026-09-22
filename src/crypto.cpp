#include "../include/crypto.hpp"
#include <cmath>
#include <map>

namespace Crypto {
    std::string xor_cipher(const std::string& data, const std::string& key) {
        std::string output = data;
        for (size_t i = 0; i < data.length(); ++i) {
            output[i] = data[i] ^ key[i % key.length()];
        }
        return output;
    }

    double calculate_entropy(const std::string& data) {
        if (data.empty()) return 0.0;
        
        std::map<char, size_t> frequencies;
        for (char c : data) frequencies[c]++;

        double entropy = 0.0;
        for (auto const& [ch, count] : frequencies) {
            double p = (double)count / data.length();
            entropy -= p * log2(p);
        }
        return entropy;
    }
}