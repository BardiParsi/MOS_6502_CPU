# **MOS6502 CPU Emulator Overview**

This project simulates a small part of the MOS6502 CPU functionality. Below is an explanation of a specific sequence:

1. **Initialization**:
   - The number of CPU cycles is set.
   - `CPU`, `Memory`, and `Stack` objects are initialized.
   - The CPU is then reset to its initial state.

2. **Fetch and Execute Cycle**:
   - The CPU fetches the first instruction, which is a `Jump to Subroutine (JSR)`.
   - Two bytes (representing the target address) are fetched from memory and pushed onto the stack.
   - The Program Counter (PC) is decremented by one to simulate the instruction cycle correctly.

3. **Custom Instruction Simulation**:
   - The CPU fetches a value from memory to simulate an in-house function:  
     `INS_LD_SV_TEMP = 0x54`.
   - This function reads one byte from a specified memory location and stores it as a temporary variable in **Zero Page** at `tempIndex = 0xC8`.

4. **Generic Address Handling**:
   - Due to differences in memory address sizes, the simulation functions are designed to handle both one-byte and two-byte memory addresses dynamically.

This simulation provides an example of how the MOS6502 operates, with a focus on the `JSR` instruction and temporary variable handling using **Zero Page** memory.

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

### **Stack Simulation
Stack
Stack class designed to handle operations related to the CPU’s stack pointer (SP).

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

├── Stack.h          Stack Simulation Header

├── LOGGER.h          Logging Utilities

├── main.cpp          Main Emulator and Test Runner

├── tests/            Unit Tests for CPU and Memory

└── CMakeLists.txt    Optional CMake support (if needed)


## License
This project is licensed under the GNU License.


