# MOS 6502 CPU Simulation in C++

This project is a simulation of the MOS 6502 CPU, implemented in C++. The MOS 6502 is an **8-bit CPU** with a 16-bit address bus, capable of addressing up to 64 KB of memory. It was a revolutionary microprocessor in the late 1970s and is still popular in retrocomputing and emulation communities. The goal of this project is to provide a clear, functional, and modular C++ implementation of the CPU, showcasing its core functionality, instruction set, and behavior.

## Features

- **Instruction Set Implementation**: Simulates the full 6502 instruction set, including addressing modes (immediate, zero page, absolute, etc.).
- **Cycle-Accurate Timing**: Emulates the clock cycle behavior of the CPU for realistic performance.
- **Memory Interface**: Includes a basic memory model to interact with the CPU for read and write operations.
- **Interrupts**: Supports hardware interrupts like IRQ and NMI.
- **Debugging Tools**: Provides logging and a step-by-step execution mode for understanding CPU operations.
- **Object-Oriented Design**: Implements the CPU in a modular and extensible way using modern C++ practices.

## Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/BardiParsi/MOS_6502_CPU.git

   
2. Build the project using your preferred C++ compiler:
   mkdir build && cd build
   cmake ..
   make

3. Run the simulator:
   ./mos6502_simulator

## License
This project is licensed under the GNU License.


