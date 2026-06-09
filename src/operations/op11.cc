#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    JP v0, addr
*/
void xsef::op11(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint16_t addr = instruction&0xFFF;

    c->pc = c->v[0]+addr;
}