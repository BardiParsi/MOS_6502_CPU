#pragma once

#include <cstdint>
#include <concepts>
#include <type_traits>
#include "memory.h"
#include "CPU.h"
#include "LOGGER.h"

using byte = uint8_t;
using twoBytes = uint16_t;
using fourBytes = uint32_t;

template<typename T>
concept addressSP = std::is_integral_v<T> &&
                    !std::is_same_v<T, bool> &&
                    (std::is_unsigned_v<T> || std::is_same_v<T, unsigned char>);



class Stack {
private:
    static constexpr twoBytes STACK_BASE = 0xFF; // Stack for Page 1
    static constexpr byte STACK_SIZE = 0xFF;

public:
    Stack() = default;
    ~Stack() = default; 

    // Initialize stack pointer
    static void reset(twoBytes& SP);

    // Push a byte onto the stack
    template<typename T>
    requires addressSP<T>
    static void pushByte(byte value, Memory& mem, fourBytes& cycles, T& SP) {
        mem[static_cast<size_t>(SP)] = value & 0xFF;
        SP--;
        cycles--;
    }

    // Push a 16-bit value onto the stack (little-endian)
    template<typename T>
    requires addressSP<T>
    static void pushShort(twoBytes value, Memory& mem, fourBytes& cycles, T& SP) {
        pushByte(value & 0xFF, mem, cycles, SP);
        pushByte((value >> 8) & 0xFF, mem, cycles, SP);
    }

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

