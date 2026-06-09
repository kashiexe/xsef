#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    SNE vx, vy
*/
void xsef::op9(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction >> 8) & 0xF;
    uint8_t y = (instruction >> 4) & 0xF;
    uint8_t last = instruction&0xF;

    if(last == 0) {
        if(c->v[x] != c->v[y]) {
            c->pc += 2;
        }
    } else {
        // unknown
    }
}