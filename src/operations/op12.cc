#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    RND vx, nn
*/
void xsef::op12(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction>>8)&0xF;
    uint8_t nn = instruction&0xFF;

    c->v[x] = rand() & nn;
}