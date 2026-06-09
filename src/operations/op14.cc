#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    SKP and SKNP vx
*/
void xsef::op14(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction>>8)&0xF;
    uint8_t first = (instruction>>4)&0xF;
    uint8_t second = instruction&0xF;

    uint8_t key = c->v[x] & 0xF;

    if(first == 9 && second == 14) {
        if(c->keypad[key]) c->pc+=2;
    } else if(first == 10 && second == 1) {
        if(!c->keypad[key]) c->pc+=2;
    } else {
        // unknown
    }
}