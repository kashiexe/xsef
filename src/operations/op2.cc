#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

void xsef::op2(void* chip, uint16_t instruction) {
    // cast as chip8
    auto* c = static_cast<CHIP8*>(chip);

    // add our current address (from PC) and jump to the address
    uint16_t addr = instruction&0xFFF;
    c->stack[c->sp] = c->pc;
    c->sp++;
    c->pc = addr;
}