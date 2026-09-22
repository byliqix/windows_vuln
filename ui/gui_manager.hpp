#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <string>
#include <vector>
#include <memory>

// Forward declarations to keep headers clean
namespace ImGui { class ImGuiContext; }

namespace ToolkitUI {
    class GuiManager {
    public:
        GuiManager();
        ~GuiManager();

        bool Initialize();
        void RenderFrame();
        bool ShouldClose();
        void Shutdown();

        // Communication with the engine
        void LogMessage(const std::string& message, int type = 0); // 0: Info, 1: Warning, 2: Error

    private:
        void DrawMainSidebar();
        void DrawHomeTab();
        void DrawKernelTab();
        void DrawSysInteractTab();
        void DrawCryptoTab();
        void DrawEvasionTab();
        void DrawNetworkTab();
        void DrawLogConsole();

        int currentTab = 0;
        std::vector<std::pair<int, std::string>> logs;
        char processSearchBuf[128] = "";
        
        // Network state
        char attackerIpBuf[64] = "127.0.0.1";
        char attackerPortBuf[16] = "4444";
    };
}

#endif