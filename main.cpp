#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "include/utils.hpp"
#include "include/crypto.hpp"
#include "include/binary.hpp"
#include "include/sys_interact.hpp"
#include "include/kernel_exploit.hpp"
#include "include/rop_scanner.hpp"
#include "include/advanced_kernel.hpp"

void show_crypto_menu() {
    std::cout << "\n" << Utils::BLUE << "--- [ CRYPTO LAB ] ---" << Utils::RESET << "\n";
    std::cout << "1. XOR Cipher (Enc/Dec)\n";
    std::cout << "2. Calculate Entropy\n";
    std::cout << "0. Return\n";
}

void show_binary_menu() {
    std::cout << "\n" << Utils::MAGENTA << "--- [ PWN-HELPER ] ---" << Utils::RESET << "\n";
    std::cout << "1. Generate Cyclic Pattern\n";
    std::cout << "2. Find Offset\n";
    std::cout << "3. Generate NOP Sled\n";
    std::cout << "4. Shellcode XOR Encoder\n";
    std::cout << "0. Return\n";
}

void show_sys_menu() {
    std::cout << "\n" << Utils::CYAN << "--- [ SYSTEM INTERACTOR ] ---" << Utils::RESET << "\n";
    std::cout << "1. Read Process Memory\n";
    std::cout << "2. Send IOCTL to Driver\n";
    std::cout << "0. Return\n";
}

void show_kernel_menu() {
    std::cout << "\n" << Utils::RED << Utils::BOLD << "--- [ KERNEL EXPLOIT LAB ] ---" << Utils::RESET << "\n";
    std::cout << "1. Classic GDI LPE (Win10/Early Win11)\n";
    std::cout << "2. Modern Data-Only Attack (Win11 22H2+)\n";
    std::cout << "3. ROP Gadget Scanner (SMEP Bypass)\n";
    std::cout << "0. Return\n";
}

int main() {
    Utils::print_banner();
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n" << Utils::BOLD << "Main Menu:" << Utils::RESET << "\n";
        std::cout << "1. Crypto Lab\n";
        std::cout << "2. Pwn-Helper\n";
        std::cout << "3. System Interactor\n";
        std::cout << "4. Kernel Exploit Lab\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            int c;
            while ((std::cin >> c) && c != 0) {
                show_crypto_menu();
                std::cout << "Choice: ";
                // logic here...
                if (c == 1) {
                    std::string d, k;
                    std::cout << "Data: "; std::cin >> d;
                    std::cout << "Key: "; std::cin >> k;
                    std::cout << Utils::GREEN << "Result: " << Crypto::xor_cipher(d, k) << Utils::RESET << "\n";
                } else if (c == 2) {
                    std::string d;
                    std::cout << "Data: "; std::cin >> d;
                    std::cout << Utils::GREEN << "Entropy: " << Crypto::calculate_entropy(d) << Utils::RESET << "\n";
                }
            }
        } else if (choice == 2) {
            int b;
            while ((std::cin >> b) && b != 0) {
                show_binary_menu();
                std::cout << "Choice: ";
                if (b == 1) {
                    size_t l; std::cout << "Len: "; std::cin >> l;
                    std::cout << Utils::GREEN << "Pattern: " << Binary::generate_cyclic_pattern(l) << Utils::RESET << "\n";
                } else if (b == 2) {
                    std::string p, cr; std::cout << "Pattern: "; std::cin >> p; std::cout << "Crash: "; std::cin >> cr;
                    std::cout << Utils::GREEN << "Offset: " << Binary::find_offset(p, cr) << Utils::RESET << "\n";
                } else if (b == 3) {
                    size_t l; std::cout << "Len: "; std::cin >> l;
                    auto s = Binary::generate_nop_sled(l);
                    std::cout << Utils::GREEN << "Sled: "; for(auto x:s) printf("%02x ", x); std::cout << Utils::RESET << "\n";
                } else if (b == 4) {
                    std::string h; uint8_t k; std::cout << "Hex SC: "; std::cin >> h; std::cout << "Key: "; std::cin >> k;
                    auto e = Binary::encode_shellcode({0x90, 0x90}, k);
                    std::cout << Utils::GREEN << "Encoded: "; for(auto x:e) printf("%02x ", x); std::cout << Utils::RESET << "\n";
                }
            }
        } else if (choice == 3) {
            int s;
            while ((std::cin >> s) && s != 0) {
                show_sys_menu();
                std::cout << "Choice: ";
                if (s == 1) {
                    DWORD p; uintptr_t a; size_t sz;
                    std::cout << "PID: "; std::cin >> p; std::cout << "Addr: "; std::cin >> std::hex >> a; std::cout << "Size: "; std::cin >> std::dec >> sz;
                    std::vector<uint8_t> buf;
                    if (SysInteract::read_process_memory(p, a, buf, sz)) {
                        std::cout << Utils::GREEN << "Data: "; for(auto x:buf) printf("%02x ", x); std::cout << Utils::RESET << "\n";
                    }
                } else if (s == 2) {
                    std::string d; DWORD c;
                    std::cout << "Device: "; std::cin >> d; std::cout << "IOCTL: "; std::cin >> std::hex >> c;
                    if (SysInteract::send_ioctl(d, c, nullptr, 0, nullptr, 0)) std::cout << Utils::GREEN << "Success!\n" << Utils::RESET;
                }
            }
        } else if (choice == 4) {
            int k;
            while ((std::cin >> k) && k != 0) {
                show_kernel_menu();
                std::cout << "Choice: ";
                if (k == 1) KernelExploit::run_lpe_exploit();
                else if (k == 2) {
                    try {
                        ModernKernel::RopScanner sc("ntoskrnl.exe");
                        auto g = sc.find_gadgets({0x58, 0xC3});
                        sc.dump_gadgets(g);
                    } catch (const std::exception& e) { std::cerr << e.what() << "\n"; }
                } else if (k == 3) AdvancedKernel::run_modern_attack();
            }
        }
    }
    std::cout << Utils::YELLOW << "Exiting... Stay safe!" << Utils::RESET << "\n";
    return 0;
}