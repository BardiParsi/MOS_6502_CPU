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
	fourBytes PC; // Program Counter
	twoBytes SP; // Stack Pointer
	byte Accumulator, indexRegister_X, indexRegister_Y; // CPU Registers
	// Processor Status
	byte carry : 1;
	byte zero : 1;
	byte intruptDisable : 1;
	byte decimal : 1;
	byte breakCommand : 1;
	byte overFlowFlag : 1;
	byte negativeFlag : 1;

public:
	static constexpr byte INS_LD_ACC_IMMID = 0xA9; // Instruction Load Accumulator Immediate Mode

	void reset(Memory& mem);
	
	byte fetch(byte& cycles, Memory& mem);

	void execute(byte cycles, Memory& mem);

};

