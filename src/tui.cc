#include "../include/xt.hpp"

std::string repeat_str(const std::string& str, size_t times) {
    std::string x = "";

    for(size_t i = 0; i < times; i++) {
        x += str;
    }

    return x;
}

/**
 * Initialize TUI for the emulator
 */
xsef::TUI::TUI(const _display& screen) {
    std::cout << "\x1b[1;1H";

    std::cout <<
    "\x1b[38;5;195;1mXSEF --- eXtremely Simple Emulator F\x1b[0m\n"         // line 1
    << "\x1b[38;5;255;1mScreen\x1b[0m\n" <<                                          // line 2
    "┏" << repeat_str("━", 64) << "┓" << std::endl;                         // line 3
    std::cout << "\x1b[36;1H┗" << repeat_str("━", 64) << "┛" <<                       // line 36
    "\n" << std::flush;                                                     // line 37
    
    this->process_screen(screen); // 32 (4-36) lines
}

void xsef::TUI::process_screen(const _display& screen) {
    std::string screen_str = "";

    for(uint8_t y = 0; y < display_height; y++) {
        screen_str += "\x1b[" + std::to_string(4 + y) + ";1H┃";;

        for(uint8_t x = 0; x < display_width; x++) {
            size_t i = y*display_width+x;
            screen_str += screen[i]?"█":" ";
        }

        screen_str += "┃";
    }

    std::cout << screen_str << std::flush;
}

void xsef::TUI::update() {
    // move the cursor up 32 lines to overwrite the screen
    // std::cout << "\033[32A";
}

void xsef::TUI::log() {

}