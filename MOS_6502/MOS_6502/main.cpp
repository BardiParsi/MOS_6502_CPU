#include <cstdint>
#include <iostream>
#include <cassert>

#include "CPU.h"
#include "Memory.h"

using std::cout;
using std::cin;


using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

int main() {
	byte cycles{2};
	Memory mem;
	CPU cpu;
	cpu.reset(mem); 
	// Start - inline simulation
	mem[0xFFFC] = CPU::INS_LD_ACC_IMMID;
	mem[0xFFFD] = 0x42;
	cout << "Memory address of mem[0xFFFD]: " << static_cast<const void*>(&mem[0xFFFD]) << endl;
	// End - inline
	cpu.execute(cycles, mem);
	return 0; 
}