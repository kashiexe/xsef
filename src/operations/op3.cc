#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/**
 * skip the next instruction if vx == kk
 */
void xsef::op3(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction >> 8) & 0xF;
    uint8_t nn = instruction & 0xFF;

    if(c->v[x] == nn) {
        c->pc += 2;
    }
}