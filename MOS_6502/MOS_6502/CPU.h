#pragma once
#include <cstdint>
#include <cassert>
#include <iostream>
#include "memory.h"

using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;
using std::cout;
using std::endl;

class CPU
{
private:

public:
	static constexpr byte INS_LD_ACC_IMMID = 0xA9, 	// Instruction Load Accumulator Immediate Mode
		INS_LD_ACC_ZP = 0xA5, // Instruction Load Accumulate Zero Page
		INS_LD_ACC_ZPX = 0xB5, // Instruction Load Accumulate Zero Page.X
		INS_JSR = 0x20; // Jump to Subroutine
	 
	fourBytes PC; // Program Counter
	twoBytes SP; // Stack Pointer
	byte accumulator, indexRegister_X, indexRegister_Y; // CPU Registers
	// Processor Status
	byte carry : 1;
	byte zero : 1;
	byte intruptDisable : 1;
	byte decimal : 1;
	byte breakCommand : 1;
	byte overFlowFlag : 1;
	byte negativeFlag : 1;

	void reset(Memory& mem);
	
	byte fetch(fourBytes& cycles, Memory& mem);

	void execute(fourBytes& cycles, Memory& mem);

	byte readByte(byte& zeroPageAddr, fourBytes& cycles, const Memory& mem);

	twoBytes fetchShort(fourBytes& cycles, Memory& mem);

	void writeShort(twoBytes value, Memory& mem, fourBytes& cycles, twoBytes& address);

	void ldAccSetStatus();
};

