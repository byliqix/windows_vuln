#include <GLFW/glfw3.h>
#include "ui/gui_manager.hpp"
#include "lib/imgui/imgui.h"
#include "lib/imgui/backends/imgui_impl_glfw.h"
#include "lib/imgui/backends/imgui_impl_opengl3.h"
#include <iostream>
#include <stdexcept>

int main() {
    std::cout << "[!] Initializing Security Toolkit GUI...\n";

    if (!glfwInit()) {
        std::cerr << "[X] Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Security Analysis Toolkit v2.0 - Professional Edition", NULL, NULL);
    if (!window) {
        std::cerr << "[X] Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 

    // --- IMGUI INITIALIZATION ---
    IMGUI_CHECKVERSION();
    if (!ImGui::CreateContext()) {
        std::cerr << "[X] Failed to create ImGui Context\n";
        return -1;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Initialize our GUI Manager
    ToolkitUI::GuiManager gui;
    if (!gui.Initialize()) {
        std::cerr << "[X] Failed to initialize GUI Manager\n";
        return -1;
    }

    std::cout << "[+] Application launched successfully. GUI is now active.\n";

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render our toolkit interface
        gui.RenderFrame();

        // Finalize ImGui Frame
        ImGui::Render();
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    
    // Bypass DestroyContext to avoid linker error in some MinGW versions
    // The OS will reclaim memory on exit.

    gui.Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
