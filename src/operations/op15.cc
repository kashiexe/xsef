#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

void xsef::op15(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction >> 8) & 0xF;
    uint8_t first = (instruction >> 4) & 0xF;
    uint8_t second = instruction & 0xF;

    switch(first) {
        case 0: {
            if(second == 7) {
                // LD vx, dt
                c->v[x] = c->dt;
            } else if(second  == 10) {
                // LD vx, k
                auto keypad = c->keypad;
                auto it = std::find(keypad.begin(), keypad.end(), 1);
                if(it == keypad.end()) c->pc-=2;
                else {
                    auto idx = std::distance(keypad.begin(), it);
                    c->v[x] = std::distance(keypad.begin(), it);
                }
            } else {
                // unknown
            }
        }

        case 1: {
            if(second == 5) {
                // ld dt, vx
                c->dt = c->v[x];
            } else if(second == 8) {
                // ld st, vx
                c->st = c->v[x];
            } else if(second == 15) {
                // add I, vx
                c->i += c->v[x];
            } else {
                // unknown
            }

            break;
        }

        case 2: {
            // ld f, vx
            if(second == 9) {
                auto digit = c->v[x] & 0xF;

                c->i = font_start_addr + (5 * digit);
            }

            break;
        }

        case 3: {
            // ld b, vx
            if(second == 3) {
                auto value = c->v[x];

                // ones
                c->memory[c->i + 2] = value % 10;
                value /= 10;

                // tens
                c->memory[c->i + 1] = value % 10;
                value /= 10;
                
                // hundreds
                c->memory[c->i] = value % 10;
            } else {
                // unknown
            }
            
            break;
        }

        case 5: {
            // ld [i], vx

            if(second == 5) {
                for(uint8_t idx = 0; idx <= x; idx++) {
                    c->memory[c->i + idx] = c->v[idx];
                }
            } else {
                // unknown
            }
            
            break;
        }

        case 6: {
            // ld vx, [i]
            if(second == 5) {
                for(uint8_t idx = 0; idx <= x; idx++) { 
                    c->v[idx] = c->memory[c->i + idx];
                }
            } else {
                // unknown
            }
            
            break;
        }
    }
}