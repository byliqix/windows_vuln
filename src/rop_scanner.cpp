#include "../include/rop_scanner.hpp"
#include "../include/utils.hpp"
#include <fstream>
#include <iomanip>

namespace ModernKernel {
    RopScanner::RopScanner(const std::string& binaryPath) : baseAddress(0) {
        if (!load_binary(binaryPath)) {
            throw std::runtime_error("Could not load binary file: " + binaryPath);
        }
        // In a real scenario, we'd parse the PE header to find the actual ImageBase
        baseAddress = 0x140000000;
    }

    RopScanner::~RopScanner() {}

    bool RopScanner::load_binary(const std::string& binaryPath) {
        std::ifstream file(binaryPath, std::ios::binary | std::ios::ate);
        if (!file) return false;

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        binaryData.resize(size);
        if (!file.read((char*)binaryData.data(), size)) return false;
        
        return true;
    }

    std::vector<RopGadget> RopScanner::find_gadgets(const std::vector<uint8_t>& pattern) {
        std::vector<RopGadget> gadgets;
        if (pattern.empty()) return gadgets;

        for (size_t i = 0; i < binaryData.size() - pattern.size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < pattern.size(); ++j) {
                if (binaryData[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                RopGadget gadget;
                gadget.address = baseAddress + i;
                gadget.bytes = pattern;
                
                // Very basic mnemonic mapping for common gadgets
                if (pattern.size() >= 2 && pattern[0] == 0x58 && pattern[1] == 0xC3) {
                    gadget.mnemonic = "pop rax; ret";
                } else if (pattern.size() >= 2 && pattern[0] == 0x59 && pattern[1] == 0xC3) {
                    gadget.mnemonic = "pop rcx; ret";
                } else {
                    gadget.mnemonic = "unknown gadget";
                }
                
                gadgets.push_back(gadget);
            }
        }
        return gadgets;
    }

    void RopScanner::dump_gadgets(const std::vector<RopGadget>& gadgets) {
        if (gadgets.empty()) {
            std::cout << Utils::RED << "[-] No gadgets found for the given pattern." << Utils::RESET << "\n";
            return;
        }

        std::cout << Utils::GREEN << "[+] Found " << gadgets.size() << " gadgets:\n" << Utils::RESET;
        std::cout << std::left << std::setw(20) << "Address" << std::setw(20) << "Bytes" << "Mnemonic" << "\n";
        std::cout << "------------------------------------------------------------\n";

        for (const auto& g : gadgets) {
            std::cout << "0x" << std::hex << g.address << Utils::RESET 
                      << "  ";
            for (auto b : g.bytes) printf("%02x ", b);
            std::cout << "  " << g.mnemonic << "\n";
        }
        std::cout << std::dec << "\n";
    }
}