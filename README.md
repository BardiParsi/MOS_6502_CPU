# **MOS6502 CPU Emulator with Google Test Environment**

This project implements a **MOS6502 CPU Emulator**, complete with memory and logging utilities, and is set up for **unit testing** using **Google Test (gtest)** in a **C++20** environment within Microsoft Visual Studio.

---

## **Project Overview**
The MOS6502 CPU Emulator simulates the behavior of the MOS6502 microprocessor, along with components like:
- **CPU operations**: Implements instructions like `INS_JSR` (Jump to Subroutine) and `INS_LD_ACC_IMMID` (Load Accumulator Immediate).
- **Memory management**: Memory simulation for addressable space.
- **Testing**: Uses Google Test for unit tests to validate CPU behavior and memory interactions.
- **Logging**: Provides insights into memory state and execution flow.

This documentation covers setting up the project, linking Google Test, and running the emulator and its tests in a **C++20** environment using **MS Visual Studio**.

---

## **Project Setup**

### **Prerequisites**
1. **Microsoft Visual Studio**:
   - Version: **2022** or newer.
   - C++ development environment installed.
2. **Google Test (gtest)**:
   - Built with **C++20** and configured for **Dynamic Debug Runtime (/MDd)**.

---

### **Environment Configuration**

#### **Step 1: Include Google Test in Visual Studio**
1. Open your Visual Studio project and go to **Project Properties**.
2. Add the following directories for `gtest`:
   - **Include Directories**:  
     ```
     C:\***\googletest\googletest\include
     ```
   - **Library Directories**:  
     ```
     C:\***\googletest\build\lib\Debug
     ```

3. Go to **Configuration Properties > Linker > Input > Additional Dependencies** and add: gtest.lib gtest_main.lib


4. Ensure the runtime library is consistent:
- **C++ Runtime Library**: Set to **Multi-threaded Debug DLL (/MDd)**.
- Match this for both your project and the `gtest.lib`.

---

#### **Step 2: Enable C++20**
1. Open **Project Properties**.
2. Go to **Configuration Properties > C/C++ > Language**.
3. Set **C++ Language Standard** to: ISO C++20 (/std:c++20)


---

#### **Step 3: Debug Build**
1. Ensure you’re working in the **Debug** configuration (top of Visual Studio).
2. Clean and rebuild the project.

---

## **Running the Emulator and Tests**

### **Main File Structure**
The `main.cpp` file initializes Google Test, runs the MOS6502 emulator simulation, and logs memory operations.

### **Memory and CPU Simulation
Memory
The Memory class provides addressable storage for the CPU.

### **CPU
Implements core MOS6502 instructions like:

INS_JSR (Jump to Subroutine)
INS_LD_ACC_IMMID (Load Accumulator Immediate)

### **Logging
The LOGGER.h utility logs:
Memory addresses
Execution flow

### **Testing Framework
Google Test Integration
Google Test is used to validate:

CPU instruction execution.
Memory read/write operations.
Logging correctness.
To run the tests:

Set up the environment as described above.
Build and run the project.
Test results will appear in the Output window of Visual Studio.

## Directory Structure
graphql
Copy code
MOS6502/

├── CPU.h             CPU Emulator Header 

├── Memory.h          Memory Simulation Header

├── LOGGER.h          Logging Utilities

├── main.cpp          Main Emulator and Test Runner

├── tests/            Unit Tests for CPU and Memory

└── CMakeLists.txt    Optional CMake support (if needed)


## License
This project is licensed under the GNU License.


