# 🛠️ Security Analysis Toolkit v2.0 - Professional Edition

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%2011%20x64-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-orange.svg)

A professional-grade security research toolkit designed for studying kernel-mode vulnerabilities, binary analysis, and defensive mitigation bypasses on Windows 11.

## 🚀 Features

### 🛡️ Kernel Exploitation Lab
- **Adaptive LPE Exploit:** Full chain for Local Privilege Escalation targeting HEVD.
- **GDI Surface Primitives:** Implementation of arbitrary kernel read/write using GDI bitmaps.
- **KASLR Bypass:** Dynamic detection of `ntoskrnl.exe` base address via `EnumDeviceDrivers`.
- **SMEP Detection:** Analysis of CR4 register to detect Supervisor Mode Execution Prevention.

### 🔍 Binary Analysis & ROP
- **PE-Aware ROP Scanner:** Scans binaries for ROP gadgets using real PE Header parsing for accurate ImageBase.
- **Pattern Matching:** Search for specific byte sequences (e.g., `pop rax; ret`).
- **Cyclic Pattern Generator:** Tools for finding buffer overflow offsets.

### 👻 Defense Evasion
- **API Hashing (FNV-1a):** Hides Windows API calls from the Import Address Table (IAT) to bypass static analysis.
- **XOR Obfuscation:** Encrypts and decrypts shellcode in memory to evade AV/EDR signatures.
- **Secure Memory Wipe:** Implements `SecureZeroMemory` to prevent forensic memory analysis.

### 🌐 Remote Control
- **Reverse Shell:** A stable Winsock-based remote access module to maintain control after escalation.
- **Command Execution:** Real-time remote command execution and output retrieval.

## 🛠️ Technical Stack
- **Language:** C++17
- **Build System:** CMake
- **GUI Framework:** ImGui (Dear ImGui)
- **Graphics API:** OpenGL 3.3 / GLFW
- **Target:** Windows 11 x64 (Kernel Mode & User Mode)

## 📦 Installation & Build

### Prerequisites
- [CMake](https://cmake.org/download/) (3.15+)
- [Visual Studio 2019/2022](https://visualstudio.microsoft.com/) with C++ Desktop Development workload.
- [GLFW](https://www.glfw.org/) and [OpenGL](https://www.opengl.org/) drivers.

### Build Steps
```bash
# 1. Create build directory
mkdir build
cd build

# 2 the Configure project
cmake ..

# 3. Build the toolkit
cmake --build . --config Release
```

## ⚠️ Disclaimer
**This tool is for educational and ethical security research purposes only.** 
The author is not responsible for any misuse of this software. Use it only on systems you own or have explicit permission to test.

---
*Developed by [byliqix](https://github.com/byliqix)*
