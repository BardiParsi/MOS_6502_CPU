#include "CPU.h"


void CPU::reset(Memory& mem) {
	PC = 0xFFFC;
	SP = 0xFF;
	carry = zero = intruptDisable = decimal = breakCommand = overFlowFlag = negativeFlag = 0;
	Accumulator = indexRegister_X = indexRegister_Y = 0;
	mem.init();
}

byte CPU::fetch(byte& cycles, Memory& mem) {
	byte data = mem.data[PC];
	PC++;
	cycles--;
	return data;
}

void CPU::execute(byte cycles, Memory& mem) {
	while (cycles > 0) {
		byte instruction = fetch(cycles, mem); // First byte is Instructor itself

		switch (instruction) {
		case INS_LD_ACC_IMMID: {
			Accumulator = fetch(cycles, mem); // Accumulator Value starts from the Second byte 
			zero = (Accumulator == 0); // Zero flag is set if the Accumulator is equal to 0
			negativeFlag = (Accumulator & 0b10000000) > 0; // Set if the bit 7 of the Accumulator is set
			break;
		}
		default: {
			break;
		}
		}

	}
}
