#ifndef MITIGATIONS_HPP
#define MITIGATIONS_HPP

#include <windows.h>
#include <psapi.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

namespace MitigationBypass {

    struct KernelModuleInfo {
        std::string name;
        uintptr_t baseAddress;
        size_t size;
    };

    class KASLRBypass {
    public:
        // Finds the base address of ntoskrnl.exe or other kernel modules
        static uintptr_t find_kernel_base(const std::string& moduleName = "ntoskrnl.exe");
        
        // Retrieves all loaded kernel modules
        static std::vector<KernelModuleInfo> enumerate_kernel_modules();

    private:
        // Internal helper to check if a module is present
        static bool is_module_loaded(const std::string& name);
    };

    class SMEPBypass {
    public:
        // Analyzes CR4 register to check if SMEP is enabled
        // Note: Actual reading of CR4 requires kernel-mode access (e.g. via your GdiPrimitive)
        static bool check_smep_status(uintptr_t cr4_value);
        
        // Calculates the bitmask needed to disable SMEP (flipping the 20th bit)
        static uintptr_t get_smep_disabled_cr4(uintptr_t current_cr4);
    };
}

#endif