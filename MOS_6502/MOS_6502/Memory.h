#pragma once
#include <algorithm> 
#include <cstdint>
#include <cassert>
#include <memory>


using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

static constexpr uint16_t KILO_BYTE = 1024;


static constexpr fourBytes max_memory = { KILO_BYTE * 64 };

class Memory
{
public:

	Memory();

	~Memory() = default; 

	std::unique_ptr<byte[]> data;

	void init();

	byte operator[] (const fourBytes& address) const;

};

