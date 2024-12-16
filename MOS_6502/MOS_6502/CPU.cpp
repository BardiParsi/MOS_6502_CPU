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
    byte lowByte = fetch(cycles, mem);
    // Fetch the high byte and shift it left by 8 bits
    byte highByte = fetch(cycles, mem);
    // Combine the high and low bytes into a 16-bit value
    twoBytes data = (highByte << 8) | lowByte;
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
            twoBytes subRout = fetchShort(cycles, mem);
            Stack::pushShort(subRout, mem, cycles, SP);
            PC--;
            cycles -= 2;
            break;
        }
        case INS_LD_SV_TEMP: {
            twoBytes indexToSave = 0x0602; // This is just for demonstration
            byte tempValue = readByte(indexToSave, cycles, mem);
            CPU::writeByte(tempValue, mem, cycles, tempIndex);
            cycles -= 3; 
            break;
        }
        default: {
            console.log("The instruction is going to fail");
            break;
        }
        } 
    }
} 
