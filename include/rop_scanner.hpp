#ifndef ROP_SCANNER_HPP
#define ROP_SCANNER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>

namespace ModernKernel {
    struct RopGadget {
        uintptr_t address;
        std::vector<uint8_t> bytes;
        std::string mnemonic;
    };

    class RopScanner {
    public:
        RopScanner(const std::string& binaryPath);
        ~RopScanner();
        
        // Mencari gadget berdasarkan pattern byte (misal: \x58\xC3 untuk 'pop rax; ret')
        std::vector<RopGadget> find_gadgets(const std::vector<uint8_t>& pattern);
        void dump_gadgets(const std::vector<RopGadget>& gadgets);

    private:
        std::vector<uint8_t> binaryData;
        uintptr_t baseAddress;
        bool load_binary(const std::string& binaryPath);
    };
}

#endif