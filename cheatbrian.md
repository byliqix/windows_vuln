# 🛡️ Windows 11 Kernel Offset Cheat Sheet
**Project:** Security Analysis Toolkit - Kernel Exploit Lab
**Target:** HackSysExtremeVulnerableDriver (HEVD) / GDI Surface Technique

---

## 📌 Overview
In Windows kernel exploitation, offsets are the "coordinates" to find critical structures in memory. Since Windows 11 uses **KASLR** and updates its structures frequently, these values may vary.

### 🗝️ Primary Structures
| Structure | Description | Use Case |
| :--- | :--- | :--- |
| `_EPROCESS` | The kernel's representation of a process | Finding the Token, PID, and Process Links |
| `_PEB` | Process Environment Block | Finding the `GdiSharedHandleTable` |
| `_GDICELL64` | GDI Cell structure | Calculating the address of `pvScan0` |

---

## 📊 Estimated Offsets (Windows 11 21H2 / 22H2 / 23H2)

> [!CAUTION]
> **WARNING:** These values are estimates. If the exploit causes a **BSOD**, your build version differs. Use the WinDbg commands below to find the exact values.

### 1. Process & Token Offsets (`_EPROCESS`)
| Constant | Estimated Offset | WinDbg Command to Verify |
| :--- | :--- | :--- |
| `UniqueProcessId` | `0x440` | `dt nt!_EPROCESS UniqueProcessId` |
| `ActiveProcessLinks` | `0x448` | `dt nt!_EPROCESS ActiveProcessLinks` |
| `Token` | `0x4b8` | `dt nt!_EPROCESS Token` |

### 2. GDI & PEB Offsets
| Constant | Estimated Offset | WinDbg Command to Verify |
| :--- | :--- | :--- |
| `PebGdiSharedTable` | `0x00f8` | `dt nt!_PEB GdiSharedHandleTable` |
| `OffsetToPvScan0` | `0x50` (`0x18 + 0x38`) | `dt nt!_SURFACE` $\rightarrow$ look for `pvScan0` |

---

## 🛠️ How to Find Exact Offsets via WinDbg

If you are running the toolkit in a VM, follow these steps to find the exact offsets for your specific build:

### Step 1: Connect WinDbg to VM
Set up kernel debugging (KDNET) and connect WinDbg to your target VM.

### Step 2: Find the Token Offset
Run this command in the WinDbg command line:
```dbg
dt nt!_EPROCESS
```
Scroll down until you find `Token`. The offset (e.g., `+0x4b8`) is what you need for `TOKEN_OFFSET`.

### Step 3: Find the Process ID Offset
Run:
```dbg
dt nt!_EPROCESS UniqueProcessId
```
The offset (e.g., `+0x440`) is your `UNIQUE_PROCESS_ID`.

### Step 4: Verify the PEB Table
To check the GDI Table offset in the PEB:
```dbg
dt nt!_PEB
```
Look for `GdiSharedHandleTable`.

---

## 🚀 Integration Guide for `security_toolkit`

To apply these offsets to your code, go to `include/kernel_exploit.hpp` and update the `WinVersionOffsets` struct:

```cpp
struct WinVersionOffsets {
    UINT_PTR uniqueProcessId = 0x440;  // Change this
    UINT_PTR activeProcLinks = 0x448;  // Change this
    UINT_PTR tokenOffset = 0x4b8;      // Change this
    UINT_PTR pebGdiSharedTable = 0x00f8;
    UINT_PTR offsetToPvScan0 = 0x50;
};
```

**Happy Hunting! Stay Safe. 💻🛡️**
