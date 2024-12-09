#include <cstdint>
#include <algorithm> 
#include <vector>
#include <cassert>


using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

static constexpr uint16_t KILO_BYTE = 1024;

struct Memory {
	static constexpr fourBytes max_memory = { KILO_BYTE * 64 };
	byte data[max_memory];

	void init() {
		std::fill(std::begin(data), std::end(data), 0); 
	}

	byte operator[] (const fourBytes& address) const {
		assert(address < max_memory); 
		return data[address];
	}
};

struct CPU {
	static constexpr byte INS_LD_ACC_IMMID = 0xA9; // Instruction Load Accumulator Immediate Mode
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

	void reset(Memory& mem) {
		PC = 0xFFFC;
		SP = 0xFF; 
		carry = zero = intruptDisable = decimal = breakCommand = overFlowFlag = negativeFlag = 0;
		Accumulator = indexRegister_X = indexRegister_Y = 0;
		mem.init();
	}

	byte fetch(byte& cycles, Memory& mem) {
		byte data = mem.data[PC];
		PC++;
		cycles--; 
		return data; 
	}

	void execute(byte cycles, Memory& mem) {
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

};

int main() {
	byte cycles{2};
	Memory mem;
	CPU cpu;
	cpu.reset(mem); 
	cpu.execute(cycles, mem);
	return 0; 
}