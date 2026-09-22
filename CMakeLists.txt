cmake_minimum_required(VERSION 3.15)
project(SecurityToolkit VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags for Windows/Security research
if(MSVC)
    add_compile_options(/W4 /EHsc /D_CRT_SECURE_NO_WARNINGS)
endif()

# Include directories
include_directories(
    include
    lib/imgui
)

# Source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "ui/*.cpp" 
    "main.cpp" 
    "main_gui.cpp"
)


# ImGui sources
set(IMGUI_SOURCES
    lib/imgui/imgui.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/backends/imgui_impl_glfw.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

# Link libraries (Assuming GLFW and OpenGL3 are available on the system)
target_link_libraries(${PROJECT_NAME} 
    opengl32 
    glfw3 
    user32 
    shell32 
    psapi
)
