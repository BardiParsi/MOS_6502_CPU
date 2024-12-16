#pragma once
#include <iostream>
#include <cstdint>
#include <cassert>
#include <concepts>
#include <type_traits>
#include "memory.h"
#include "Stack.h"
#include "LOGGER.h"

using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;
using std::cout;
using std::endl;

// Concept to ensure that T is an integral type, not a bool, and is either unsigned
// or a type that is compatible with unsigned char. This ensures the type used for 
// memory addresses is a valid unsigned integer type (e.g., uint8_t, uint16_t, uint32_t).
template<typename T>
concept addressMem = std::is_integral_v<T> && 
					 !std::is_same_v<T, bool> && 
					 (std::is_unsigned_v<T> || std::is_same_v<T, unsigned char>);

class CPU
{
private:

public:
	static constexpr byte INS_LD_ACC_IMMID = 0xA9, 	// Instruction Load Accumulator Immediate Mode
		INS_LD_ACC_ZP = 0xA5, // Instruction Load Accumulate Zero Page
		INS_LD_ACC_ZPX = 0xB5, // Instruction Load Accumulate Zero Page.X
		INS_JSR = 0x20, // 0x20 Jump to Subroutine but in this version we go upside down
	    INS_LD_SV_TEMP = 0x54; // In house created Instructor for Load and Save at the same time
	 
	byte tempIndex = 0xc8; // An index to save a temporary variable

	twoBytes PC; // Program Counter
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

	CPU() = default;
	~CPU() = default; 
	
	// The writeByte method uses the addressMem concept to allow addressing with any 
	// integral type (unsigned char, uint16_t, uint32_t, etc.). This makes the method 
	// flexible enough to work with different address sizes and types.
	template<typename T>
	requires addressMem<T>
	void writeByte(byte value, Memory& mem, fourBytes& cycles, T& address) {
		mem[static_cast<byte>(address)] = value & 0xFF; 
		cycles--;
	}

	template<typename T>
	requires addressMem<T>
	void writeShort(twoBytes value, Memory& mem, fourBytes& cycles, T& address) {
		writeByte(value & 0xFF, mem, cycles, address);
		address++;
		writeByte((value >> 8) & 0xFF, mem, cycles, address);
	}


	void reset(Memory& mem);
	
	byte fetch(fourBytes& cycles, Memory& mem);

	void execute(fourBytes& cycles, Memory& mem);

	template<typename T>
	requires addressMem<T>
	byte readByte(T& address, fourBytes& cycles, const Memory& mem) {
		byte data = mem[address];
		cycles--;
		return data;
	}

	twoBytes fetchShort(fourBytes& cycles, Memory& mem);

	void ldAccSetStatus();

};

