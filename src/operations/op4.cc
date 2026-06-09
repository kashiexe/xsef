#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    SNE vx, byte
    if vx != nn
*/
void xsef::op4(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction & 0xF00) >> 8;
    uint8_t nn = instruction & 0xFF;

    if(c->v[x] != nn) {
        c->pc += 2;
    }
}