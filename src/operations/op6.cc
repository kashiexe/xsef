#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    LD vx, byte
    (loads nn into vx)
*/
void xsef::op6(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction & 0xF00) >> 8;
    uint8_t nn = instruction & 0xFF;

    c->v[x] = nn;
}