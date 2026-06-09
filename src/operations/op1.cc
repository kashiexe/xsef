#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/// @brief 1nnn - JP to addr nnn (1-4095)
/// @param chip 
/// @param instruction 
void xsef::op1(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    // decode nnn
    uint16_t nnn = instruction & 0xFFF;

    // JP to addr nnn
    c->pc = nnn;
} 