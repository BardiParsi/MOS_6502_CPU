#include "Memory.h"


Memory::Memory() : data(std::make_unique<byte[]>(max_memory)) {
	init();
}

void Memory::init() {
	std::fill(data.get(), data.get() + max_memory, 0);
}

byte Memory::operator[] (const fourBytes& address) const {
	assert(address < max_memory);
	return data[address];
}