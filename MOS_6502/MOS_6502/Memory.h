#pragma once
#include <algorithm> 
#include <cstdint>
#include <cassert>


using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

static constexpr uint16_t KILO_BYTE = 1024;


static constexpr fourBytes max_memory = { KILO_BYTE * 64 };

class Memory
{
public:
	byte data[max_memory];

	void init() {
		std::fill(std::begin(data), std::end(data), 0);
	}

	byte operator[] (const fourBytes& address) const {
		assert(address < max_memory);
		return data[address];
	}
};

