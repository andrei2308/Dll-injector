# DLL Injector

A simple and straightforward DLL Injector for Windows, written in C++. This project demonstrates how to inject a DLL into a target process using Windows API functions such as `OpenProcess`, `VirtualAllocEx`, and `CreateRemoteThread`.

## Features

- Injects a custom DLL into a running process by its name.
- Uses basic Windows API functions for memory allocation and thread creation in the target process.
- Easy to understand and extend for educational purposes.

---

## Prerequisites

- **Windows OS**: This project is designed for the Windows operating system.
- **C++ Compiler**: Ensure you have a C++ compiler like GCC (MinGW) or Microsoft Visual Studio.
- **Administrator Privileges**: Required to inject the DLL into processes with elevated permissions.

---

## Usage

### 1. Clone the Repository
```bash
git clone https://github.com/andrei2308/Dll-injector.git
cd Dll-injector
```

### 2. Compile the Code

#### **DLL Compilation**
Save your DLL code (e.g., `example_dll.cpp`) in the same directory and compile it as a DLL.

**Using MinGW:**
```bash
g++ -shared -o example_dll.dll example_dll.cpp -luser32
```

**Using Visual Studio:**
1. Create a new project for a **Dynamic Link Library (DLL)**.
2. Add your `example_dll.cpp` file to the project.
3. Build the project to generate `example_dll.dll`.

#### **Injector Compilation**
Compile the injector executable.

**Using MinGW:**
```bash
g++ -o injector.exe injector.cpp
```

**Using Visual Studio:**
1. Create a new project for a **Console Application**.
2. Add `injector.cpp` to the project.
3. Build the project to generate `injector.exe`.

---

### 3. Run the Injector
Identify the **Process ID (PID)** of the target process:
1. Open Task Manager (`Ctrl+Shift+Esc`) and locate the process.
2. Note its PID from the **Details** tab.

Run the injector with the path to your compiled DLL and the target PID:
```bash
injector.exe <path-to-dll> <PID>
```

#### Example:
```bash
injector.exe C:\path\to\example_dll.dll 1234
```

---

## How It Works

1. The injector opens the target process using `OpenProcess`.
2. Memory is allocated in the target process using `VirtualAllocEx`.
3. The DLL path is written into the allocated memory using `WriteProcessMemory`.
4. A remote thread is created in the target process to execute `LoadLibraryA` and load the DLL.

---

## Notes

- **Error Handling:** Make sure the injector is run with the appropriate permissions. Administrator rights may be needed for some processes.
- **Antivirus Warnings:** This program may be flagged by antivirus software. Use responsibly.
- **32-bit vs 64-bit:** The architecture of the injector, DLL, and target process must match (e.g., all 64-bit or all 32-bit).

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

---

## Disclaimer

This project is intended for educational purposes only. Use it responsibly and ensure you have permission before injecting a DLL into any process.

---
