/*
    XSef's Utility Interface
*/
#ifndef XUTILS
#define XUTILS

// std library includes
#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<memory>
#include<algorithm>
#include<cctype>
#include<fstream>
#include<sstream>
#include<array>
#include<math.h>
#include<random>
#include<unistd.h>
#include<termios.h>
#include<thread>
#include<chrono>

namespace xsef {
    // necessary constants
    const uint16_t KB               =  1024;
    const uint8_t display_width     =  64;
    const uint8_t display_height    =  32;
    const uint16_t dimensions       =  display_width*display_height;
    const uint8_t vregs             =  16;
    const uint16_t mem_capacity     =  4*KB;
    const uint16_t font_start_addr  =  0x50;
    const uint16_t program_start    =  0x200;
    const uint16_t max_mem          =  0xFFF;    // highest address in memory
    const uint16_t cfps             =  500;      // cpu runs at 500hz
    const uint8_t fps               =  60;       // terminal refresh rate and OS dump itself should only run at 60hz

    // display
    using _display = std::array<uint8_t, dimensions>;

    // simple helper function to lower a string instead of just a character
    std::string lower(std::string str);

    std::string readf(const std::string& path);
}

#endif