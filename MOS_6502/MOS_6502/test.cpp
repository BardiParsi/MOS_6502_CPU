
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

}






