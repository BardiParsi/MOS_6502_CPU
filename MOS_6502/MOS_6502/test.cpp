
// Remove #if 0 and #endif to activate the Gtest
#if 0

#include <cstdint>
#include <iostream>
#include <cassert>
#include <gtest/gtest.h>
#include "CPU.h"
#include "Memory.h"
#include "Stack.h"
#include "LOGGER.h"



using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

class MOS6502Test : public testing::Test {
public:
	fourBytes cycles{ 7 };
	Memory mem;
	CPU cpu{};
	
	
	virtual void setup() {
		cpu.reset(mem);
		// Write all the variable initialization here
	}
	virtual void TearDown() {

	}
};

TEST_F(MOS6502Test, Test_Init) {
	mem[0xFFFC] = CPU::INS_JSR;
	mem[0xFFFD] = 0x33;
	mem[0xFFFE] = 0x54;
	cpu.execute(cycles, mem);
	
	EXPECT_EQ(mem[0xFF], 0x33);
	EXPECT_EQ(mem[0xFE], 0x54);
	EXPECT_EQ(mem[0xc8], 0x85);
}





#endif
