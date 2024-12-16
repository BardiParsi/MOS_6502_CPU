#include "Stack.h"

void Stack::reset(twoBytes& SP) {
    SP = STACK_BASE;
}

byte Stack::popByte(Memory& mem, fourBytes& cycles, twoBytes& SP) {
    SP++;
    cycles--;
    return mem[STACK_BASE + SP];
}

twoBytes Stack::popShort(Memory& mem, fourBytes& cycles, twoBytes& SP) {
    byte low = popByte(mem, cycles, SP);
    byte high = popByte(mem, cycles, SP);
    return static_cast<twoBytes>((high << 8) | low);
}

byte Stack::peek(const Memory& mem, const twoBytes& SP) {
    return mem[SP];
}

bool Stack::isEmpty(const twoBytes& SP) {
    return SP == STACK_BASE;
}

bool Stack::isFull(const twoBytes& SP) {
    return SP == 0x00;
}