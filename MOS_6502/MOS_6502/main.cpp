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
	fourBytes cycles{ 7 };
	Memory mem;
	CPU cpu{};
	cpu.reset(mem);
	// Start - inline simulation testing
	mem[0x0] = CPU::INS_JSR;
	mem[0x1] = 0x33;
	mem[0x2] = 0x54;
	// mem[0x4242] = CPU::INS_LD_ACC_IMMID;
	// mem[0x4243] = 0x84;

	console.log("Memory address of mem[0x0]:", static_cast<const void*>(&mem[0x0]));
	console.log("Memory address of mem[0x1]:", static_cast<const void*>(&mem[0x1]));
	console.log("Memory address of mem[0x2]:", static_cast<const void*>(&mem[0x2]));
	// console.log("Memory address of mem[0x4242]:", static_cast<const void*>(&mem[0x4242]));
	// console.log("Memory address of mem[0x4243]:", static_cast<const void*>(&mem[0x4243]));
	// End - inline
	cpu.execute(cycles, mem);
	console.log("The value of Accumulator is:", CPU::INS_LD_ACC_IMMID);
	cpu.SP -= 0x1;
	std::stringstream ss;
	ss << "0x" << std::hex << static_cast<int>(cpu.SP);
	console.log(ss.str());
	console.log(mem[0X1001]);

	return 0;
}




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