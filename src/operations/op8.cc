#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    direct operations on vx with vy
*/
void xsef::op8(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction & 0xF00) >> 8;
    uint8_t y = (instruction & 0xF0)  >> 4;
    uint8_t subop = instruction & 0xF;

    switch(subop) {
        // vx := vy
        case 0:
            c->v[x] = c->v[y];
            break;

        // vx |= vy
        case 1:
            c->v[x] |= c->v[y];
            break;

        // vx &= vy
        case 2:
            c->v[x] &= c->v[y];
            break;

        // vx ^= vy
        case 3:
            c->v[x] ^= c->v[y];
            break;
        
        // vx += vy
        case 4: {
            int sum = c->v[x] + c->v[y];

            // vf = 1 on carry
            c->v[15] = (sum > 255) ? 1 : 0;

            c->v[x] = sum & 0xFF; 
            break;
        }

        // vx -= vy
        case 5: {
            int sub = c->v[x] - c->v[y];

            // vf = 0 on borrow
            c->v[15] = (sub < 0) ? 0 : 1;

            c->v[x] = sub & 0xFF;
            break;
        }

        // vx >>= 1
        case 6: {
            // old LSB in vf
            c->v[15] = c->v[x]&0x1;

            c->v[x] >>= 1;
            break;
        }

        // vx =- vy
        case 7: {
            int sub = c->v[y] - c->v[x];

            // vf = 0 on borrow
            c->v[15] = (sub < 0) ? 0 : 1;

            c->v[x] = sub & 0xFF;
            break;
        }

        // vx <<= 1
        case 14:
            // old MSB in vf
            c->v[15] = (c->v[x] >> 7) & 0x1;

            c->v[x] <<= 1;
            break;

        // unknown case
        default:
            break;
    }
}