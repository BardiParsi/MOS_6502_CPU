#pragma once
#include <cstdint>
#include "memory.h"
#include "CPU.h"

using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

class Stack {
private:
    static constexpr twoBytes STACK_BASE = 0x1000; // Stack starts at 0x1000
    byte STACK_SIZE = 0x2;

public:
    Stack() = default;
    ~Stack() = default; 

    // Initialize stack pointer
    static void reset(twoBytes& SP);

    // Push a byte onto the stack
    static void pushByte(byte value, Memory& mem, fourBytes& cycles, twoBytes& SP);

    // Push a 16-bit value onto the stack (little-endian)
    static void pushShort(twoBytes value, Memory& mem, fourBytes& cycles, twoBytes& SP);

    // Pop a byte from the stack
    static byte popByte(Memory& mem, fourBytes& cycles, twoBytes& SP);

    // Pop a 16-bit value from the stack (little-endian)
    static twoBytes popShort(Memory& mem, fourBytes& cycles, twoBytes& SP);

    // Peek at the top byte of the stack without popping
    static byte peek(const Memory& mem, const twoBytes& SP);

    // Check if stack is empty (SP = 0xFF)
    static bool isEmpty(const twoBytes& SP);

    // Check if stack is full (SP = 0x00)
    static bool isFull(const twoBytes& SP);
};

