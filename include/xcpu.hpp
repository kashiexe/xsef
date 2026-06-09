#ifndef XCPU
#define XCPU

#include "xutils.hpp"
#include "xops.hpp"
#include "xt.hpp"

namespace xsef {
    /**
     * class containing CHIP8 specifications and the fetch-decode-execute loop 
     */
    class CHIP8 {
        public:
            std::unique_ptr<TUI> tui;
            std::array<uint8_t, mem_capacity> memory{};
            _display display;
            std::array<uint16_t, 16> stack{};
            std::array<uint8_t, vregs> v{}; // 16 8-bit registers
            std::array<uint8_t, 16> keypad{};
            std::array<uint8_t, 16> keylife{}; // key "cache"

            uint8_t sp      = 0;
            uint16_t pc     = program_start; // pc starts at 0x200
            uint16_t i      = 0;
            uint8_t dt      = 0; // delay timer
            uint8_t st      = 0; // sound timer

            explicit CHIP8(const std::string& rom);
            ~CHIP8() = default;

            void load_characters();
            void load_rom(const std::string& rom_path);
            void update_keypad(char c);
    };
}

#endif