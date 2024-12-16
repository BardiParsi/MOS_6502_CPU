#include <cstdint>
#include <iostream>
#include "CPU.h"
#include "Memory.h"
#include "Stack.h"
#include "LOGGER.h"
#include <gtest/gtest.h>
#include <sstream>

using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;



int main() {
	fourBytes cycles{ 13 };
	Memory mem;
	CPU cpu{};
	Stack stack{};
	cpu.reset(mem);
	// Start - inline simulation testing
	mem[0xFFFC] = CPU::INS_JSR;
	mem[0xFFFD] = 0x33;
	mem[0xFFFE] = 0x54;
	mem[0x0602] = 0x85;

	console.log("Memory address of mem[0x0]:", static_cast<const void*>(&mem[0xFFFC]));
	console.log("Memory address of mem[0x1]:", static_cast<const void*>(&mem[0xFFFD]));
	console.log("Memory address of mem[0x2]:", static_cast<const void*>(&mem[0xFFFE]));
	console.log("Memory address of mem[0x0601]:", static_cast<const void*>(&mem[0x0601]));
	console.log("Memory address of mem[0x0602]:", static_cast<const void*>(&mem[0x0602]));
	// End - inline testing
	cpu.execute(cycles, mem);
	console.log("The value of Accumulator is:", CPU::INS_LD_ACC_IMMID);
	
	std::stringstream ss;
	ss << "0x" << std::hex << static_cast<int>(cpu.SP);
	console.log(ss.str());
	console.log(mem[0xFF]);
	console.log(mem[0xFE]);
	console.log(mem[cpu.tempIndex]);

	return 0;
}

// Remove if 0 and #endif to activate the gtest
#if 0

#if GTEST_OS_ESP8266 || GTEST_OS_ESP32
extern "C" {
#endif
	void setup() {
		testing::InitGoogleTest();
	}

	void loop() { RUN_ALL_TESTS(); }

#if GTEST_OS_ESP8266
}
#endif

#endif