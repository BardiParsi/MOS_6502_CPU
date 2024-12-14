#include <cstdint>
#include <iostream>
#include <cassert>

#include "CPU.h"
#include "Memory.h"
#include "LOGGER.h"

using std::cout;
using std::cin;

using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

int main() {
	fourBytes cycles{7};
	Memory mem;
	CPU cpu{};
	cpu.reset(mem); 
	// Start - inline simulation testing
	mem[0xFFFC] = CPU::INS_JSR;
	mem[0xFFFD] = 0x33;
	mem[0xFFFE] = 0x54;
	mem[0x4242] = CPU::INS_LD_ACC_IMMID;
	mem[0x4243] = 0x84; 
	console.log("Memory address of mem[0xFFFC]:", static_cast<const void*>(&mem[0xFFFC]));
	console.log("Memory address of mem[0xFFFD]:", static_cast<const void*>(&mem[0xFFFD]));
	console.log("Memory address of mem[0xFFFE]:", static_cast<const void*>(&mem[0xFFFE]));
	console.log("Memory address of mem[0x4242]:", static_cast<const void*>(&mem[0x4242]));
	console.log("Memory address of mem[0x4243]:", static_cast<const void*>(&mem[0x4243]));
	// End - inline
	cpu.execute(cycles, mem);
	cout << cpu.accumulator << endl; 
	return 0; 
}