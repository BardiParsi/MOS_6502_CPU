#include "CPU.h"


void CPU::reset(Memory& mem) {
	PC = 0x0;
    SP = 0X1000; 
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
	byte data = fetch(cycles, mem);
	data |= (fetch(cycles, mem) << 8); // Move 1 byte to the left and do OR bitwise assignment to make a 16 bit out of 8 bit CPU
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
        if(instruction) console.log("The instruction pointing to:", instruction);

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
            std::cout << SP << std::endl; 
            twoBytes subRout = fetchShort(cycles, mem);
            console.log(PC - 1);
            Stack::pushByte((PC - 1), mem, cycles, SP); 
            console.log(PC);
            Stack::pushByte(PC, mem, cycles, SP);
            PC -=2;
            cycles -= 2;
            break;
        }
        default: {
            console.log("The instruction is going to fail");
            break;
        }
        } 
    }
} 
