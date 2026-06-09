#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    LD I, addr
*/
void xsef::op10(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint16_t addr = instruction&0xFFF;

    c->i = addr;
}