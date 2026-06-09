/*
    xsef

    =====================================================================================

    In order to get xsef to actually do something, the user must input a path to a valid ROM (otherwise it will just do random garbage)
    there are many ROMs out there, just search "chip8 ROMs" (or go to github.com/kripod/chip8-roms), download one you want and test it

    =====================================================================================

    Kashi // 09.06.2026
*/
#include "../include/xsef.hpp"

int main(int argc, char** argv) {
    if(argc > 1) {
        std::string path = argv[1];

        // initialize CHIP8 with the rom provided
        if(std::filesystem::exists(path)) {
            xsef::CHIP8 chip(path);
        } else {
            std::cout << "\x1b[38;5;160;1m[xsef]: \x1b[0m\x1b[38;5;255mThis ROM (\x1b[1m" << path << "\x1b[0m\x1b[38;5;255m) does NOT exist!\x1b[0m" << std::endl;
        }
    } else {
        std::cout << "\x1b[38;5;160;1m[xsef]: \x1b[0m\x1b[38;5;255mPlease make sure to load a ROM by calling xsef with 'xsef my_rom.ch8'\x1b[0m" << std::endl;
    }

    return 0;
}