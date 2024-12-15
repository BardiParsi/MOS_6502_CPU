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
	mem[0x0] = CPU::INS_JSR;
	mem[0x1] = 0x33;
	mem[0x2] = 0x54;
	
	console.log("Memory address of mem[0xFFFC]:", static_cast<const void*>(&mem[0x0]));
	console.log("Memory address of mem[0xFFFD]:", static_cast<const void*>(&mem[0x1]));
	console.log("Memory address of mem[0xFFFE]:", static_cast<const void*>(&mem[0x2]));

	// End - inline
	cpu.execute(cycles, mem);
	console.log("The value of Accumulator is:", CPU::INS_LD_ACC_IMMID);
	// Currently SP is pointing at 0x10FF
	EXPECT_EQ(mem[0x1002], 0x54);
}






