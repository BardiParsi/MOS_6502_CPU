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
	fourBytes cycles{3};
	Memory mem;
	CPU cpu{};
	cpu.reset(mem); 
	// Start - inline simulation testing
	mem[0xFFFC] = CPU::INS_LD_ACC_ZP;
	mem[0xFFFD] = 0x33;
	mem[0x0033] = 0x54;
	cout << "Memory address of mem[0xFFFD]: " << static_cast<const void*>(&mem[0xFFFD]) << endl;
	cout << "Memory address of mem[0x0033]: " << static_cast<const void*>(&mem[0x0033]) << endl;
	// End - inline
	cpu.execute(cycles, mem);
	cout << cpu.accumulator << endl; 
	return 0; 
}