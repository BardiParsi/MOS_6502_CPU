#include "CPU.h"


void CPU::reset(Memory& mem) {
	PC = 0xFFFC;
	SP = 0xFF;
	carry = zero = intruptDisable = decimal = breakCommand = overFlowFlag = negativeFlag = 0;
	accumulator = indexRegister_X = indexRegister_Y = 0;
	mem.init();
}

byte CPU::fetch(fourBytes& cycles, Memory& mem) {
	byte data = mem[PC];
	PC++;
	cycles--;
	return data;
}

twoBytes CPU::fetchShort(fourBytes& cycles, Memory& mem) {
	// Little Endian CPU capacity is 8 Bit format
	// Memory Address is 16 Bit
	byte data = mem[PC];
	PC++;
	data |= (mem[PC] << 8); // Move 1 byte to the left and do OR bitwise assignment to make a 16 bit out of 8 bit CPU
	PC++;
	cycles-=2;

	return data;
}


byte CPU::readByte(byte& zeroPageAddr, fourBytes& cycles, const Memory& mem) {
	byte data = mem[zeroPageAddr];
	cycles--; 
	return data;
}

void CPU::ldAccSetStatus() {
	zero = (accumulator == 0); // Zero flag is set if the Accumulator is equal to 0
	negativeFlag = (accumulator & 0b10000000) > 0; // Set if the bit 7 of the Accumulator is set

}

void CPU::execute(fourBytes& cycles, Memory& mem) {

    while (cycles > 0) {

        byte instruction = fetch(cycles, mem); // First byte is Instruction itself
        cout << instruction << endl;

        switch (instruction) {

        case INS_LD_ACC_IMMID: {
            accumulator = fetch(cycles, mem); // Accumulator Value starts from the second byte 
            ldAccSetStatus();
            break;
        }
        case INS_LD_ACC_ZP: {
            byte zeroPageAddr = fetch(cycles, mem);
            accumulator = readByte(zeroPageAddr, cycles, mem);
            ldAccSetStatus();
            break;
        }
        case INS_LD_ACC_ZPX: {
            byte zeroPageAddr = fetch(cycles, mem);
            zeroPageAddr += indexRegister_X;
            cycles--;
            accumulator = readByte(zeroPageAddr, cycles, mem);
            ldAccSetStatus();
            break;
        }
        case INS_JSR: {
            twoBytes subRoutAddr = fetchShort(cycles, mem);
            writeShort(subRoutAddr, mem, cycles, SP);
            PC = subRoutAddr; 
            cycles--;
            break;
        }
        default: {
            cout << "The instruction is going to fail" << endl;
            break;
        }
        } 
    }
} 
