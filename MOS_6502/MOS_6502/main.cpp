#include <cstdint>
#include <algorithm> 
#include <vector>
#include <cassert>
#include "CPU.h"
#include "Memory.h"


using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

int main() {
	byte cycles{2};
	Memory mem;
	CPU cpu;
	cpu.reset(mem); 
	cpu.execute(cycles, mem);
	return 0; 
}