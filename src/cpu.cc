#include "../include/xsef.hpp"

char getch() {
    char buf = 0;
    
    // read character
    if(read(STDIN_FILENO, &buf, 1) < 0) buf = 0;

    return buf;
}

void xsef::CHIP8::update_keypad(char c) {
    switch(c) {
        case '1':
            this->keylife[1] = 4;
            break;
        case '2':
            this->keylife[2] = 4;
            break;
        case '3':
            this->keylife[3] = 4;
            break;
        case '4':
            this->keylife[12] = 4;
            break;
        case 'q':
        case 'Q':
            this->keylife[4] = 4;
            break;
        case 'w':
        case 'W':
            this->keylife[5] = 4;
            break;
        case 'e':
        case 'E':
            this->keylife[6] = 4;
            break;
        case 'r':
        case 'R':
            this->keylife[13] = 4;
            break;
        case 'a':
        case 'A':
            this->keylife[7] = 4;
            break;
        case 's':
        case 'S':
            this->keylife[8] = 4;
            break;
        case 'd':
        case 'D':
            this->keylife[9] = 4;
            break;
        case 'f':
        case 'F':
            this->keylife[14] = 4;
            break;
        case 'z':
        case 'Z':
            this->keylife[10] = 4;
            break;
        case 'x':
        case 'X':
            this->keylife[0] = 4;
            break;
        case 'c':
        case 'C':
            this->keylife[11] = 4;
            break;
        case 'v':
        case 'V':
            this->keylife[15] = 4;
            break;
    }
}


void xsef::CHIP8::load_characters() {
    const size_t FONTSET_SIZE = 80;

    uint8_t fontset[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for(size_t i = 0; i < FONTSET_SIZE; i++) {
        this->memory[font_start_addr + i] = fontset[i]; 
    }
}


void xsef::CHIP8::load_rom(const std::string& rom_path) {
    // read file into a uint8_t buffer
    std::ifstream file(rom_path, std::ios::binary | std::ios::ate);

    if(!file.is_open()) {
        std::cerr << "Failed to open ROM" << std::endl;
        return;
    }

    auto size = file.tellg();
    std::vector<uint8_t> buffer(size);

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    file.close();

    // load that buffer in memory and since programs start at 0x200 it should load all bytes at 0x200+i
    for(size_t i = 0; i < buffer.size(); i++) {
        if((program_start + i) < max_mem) {
            memory[program_start+i] = buffer[i];
        }
    }
}

xsef::CHIP8::CHIP8(const std::string& rom) {
    // clear terminal
    std::cout << "\x1b[2J\x1b[1;1H";

    // save current terminal settings and set terminal to raw mode
    struct termios old_settings;

    // save current terminal settings
    if(tcgetattr(STDIN_FILENO, &old_settings) < 0) return;
    
    struct termios new_settings = old_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 0;

    // apply new settings
    if(tcsetattr(STDIN_FILENO, TCSANOW, &new_settings) < 0) return;

    // load the rom
    load_rom(rom);

    // load the characters into memory (from 0x050)
    this->load_characters();

    // initialize TUI
    std::fill(display.begin(), display.end(), 0);
    tui = std::make_unique<TUI>(this->display);

    // main loop
    bool running = true;
    while(running) {
        // character
        char c = getch();
        
        if(c == 'p') {
            running = false;
        } else if (c != 0) { 
            update_keypad(c);
        }

        // update keypad depending on keylife
        for (uint8_t i = 0; i < 16; i++) {
            keypad[i] = keylife[i] > 0;

            if (keylife[i] > 0) {
                keylife[i]--;
            }
        }

        // fetch-decode-execute loop
        for(uint8_t i = 0; i < (cfps/fps); i++) {
            // fetch instruction from memory (2 bytes since instructions are 16 bits) 
            uint16_t instruction = (memory[pc] << 8) | memory[pc + 1];

            // decode instruction 
            uint8_t opcode = (instruction >> 12) & 0xF;

            // advance pc by 2 to skip to the next instruction (since each instruction is 2 bytes)
            pc += 2;

            // execute instruction
            operations[opcode](this, instruction);
        }

        // update timers
        if(dt > 0) dt--;
        if(st > 0) st--;

        // update screen
        tui->update();
        tui->process_screen(display);

        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1000.0/fps));
    }
    
    // restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}