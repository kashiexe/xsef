#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

void xsef::op0(void* chip, uint16_t instruction) {
    // first, we cast the chip to the actual class to access its members
    auto* c = static_cast<CHIP8*>(chip);

    // now we decode x and y to check if they're 0 and E respectively (otherwise it's an unknown instruction)
    uint8_t x = (instruction >> 8) & 0xF;
    uint8_t y = (instruction >> 4) & 0xF;

    if(x == 0 && y == 0xE) {
        // check if n is 0 or E to determine if it's CLS or RET
        uint8_t n = instruction & 0xF;

        // CLS
        if(n == 0) {
            std::fill(c->display.begin(), c->display.end(), 0);
        } else if(n == 0xE) {
            // RET (goes back to the PC last saved in stack)
            c->sp--;
            c->pc = c->stack[c->sp];
        } else {
            // unknown instruction
        }
    } else {
        // unknown instruction
    }
}