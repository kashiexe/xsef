#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    SE vx, vy
*/
void xsef::op5(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction & 0xF00) >> 8;
    uint8_t y = (instruction & 0xF0) >> 4;
    uint8_t last = instruction&0xF;

    if(last == 0) {
        if(c->v[x] == c->v[y]) {
            c->pc += 2;
        }
    } else {
        // unknown
    }
}