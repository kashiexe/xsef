#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    ADD vx, byte
    (adds nn to vx)
*/
void xsef::op7(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction & 0xF00) >> 8;
    uint8_t nn = instruction & 0xFF;

    c->v[x] += nn;
}