#include "../../include/xops.hpp"
#include "../../include/xcpu.hpp"

/*
    DRW vx, vy, n

    this one is a bit longer than the others
*/
void xsef::op13(void* chip, uint16_t instruction) {
    auto* c = static_cast<CHIP8*>(chip);

    uint8_t x = (instruction>>8)&0xF;
    uint8_t y = (instruction>>4)&0xF;
    uint8_t n = instruction&0xF;

    // wrap around display boundaries
    uint8_t posx = c->v[x] % display_width;
    uint8_t posy = c->v[y] % display_height;

    c->v[15] = 0;

    for(size_t row = 0; row < n; row++) {
        uint8_t current_y = posy + row;

        // clip vertically
        if(current_y >= display_height) break;
        
        uint8_t sprite_byte = c->memory[c->i + row];

        for(size_t col = 0; col < 8; col++) {
            uint8_t current_x = posx + col;

            // clip horizontally
            if(current_x >= display_width) break;

            uint8_t sprite_pixel = sprite_byte & (0x80 >> col);
            uint8_t* screen_pixel = &c->display[current_y * display_width + current_x];

            if(sprite_pixel != 0) {
                // screen pixel is also on this place, collision
                if(*screen_pixel == 1) {
                    c->v[15] = 1;
                }

                // XOR with sprite pixel
                *screen_pixel ^= 1;
            }
        }
    }

    c->tui->process_screen(c->display);
}