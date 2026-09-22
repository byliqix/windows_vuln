#include "../include/rop_scanner.hpp"
#include "../include/utils.hpp"
#include <fstream>
#include <iomanip>
#include <windows.h>

namespace ModernKernel {
    RopScanner::RopScanner(const std::string& binaryPath) : baseAddress(0) {
        if (!load_binary(binaryPath)) {
            throw std::runtime_error("Could not load binary file: " + binaryPath);
        }

        // Professional PE Header Parsing to find ImageBase
        if (binaryData.size() < 0x100) throw std::runtime_error("Binary too small to be a valid PE");

        // DOS Header -> e_lfanew
        uint32_t peOffset = *(uint32_t*)(&binaryData[0x3C]);
        if (peOffset + 0x20 > binaryData.size()) throw std::runtime_error("Invalid PE offset");

        // PE Signature check "PE\0\0"
        if (*(uint32_t*)(&binaryData[peOffset]) != 0x00004550) throw std::runtime_error("Not a valid PE file");

        // NT Header -> Optional Header -> ImageBase
        // Offset: PE signature(4) + File Header(20) + Magic(2) = 26 bytes from PE offset
        // On x64, ImageBase is at offset 24 from the start of Optional Header
        uintptr_t imageBase = *(uintptr_t*)(&binaryData[peOffset + 24 + 24]); 
        
        baseAddress = imageBase;
        std::cout << "\t[+] Parsed PE Header. ImageBase: 0x" << std::hex << baseAddress << Utils::RESET << std::dec << "\n";
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

                if (pattern.size() >= 2 && pattern[0] == 0x58 && pattern[1] == 0xC3) {
                    gadget.mnemonic = "pop rax; ret";
                } else if (pattern.size() >= 2 && pattern[0] == 0x59 && pattern[1] == 0xC3) {
                    gadget.mnemonic = "pop rcx; ret";
                } else if (pattern.size() >= 2 && pattern[0] == 0x5C && pattern[1] == 0xC3) {
                    gadget.mnemonic = "pop rsp; ret";
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