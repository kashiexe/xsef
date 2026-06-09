#ifndef XT
#define XT

#include "xutils.hpp"

namespace xsef {
    class TUI {
        public:
            uint8_t sp = 0;
            std::array<uint8_t, vregs> v;

            TUI(const _display& screen);
            ~TUI() = default;

            void process_screen(const _display& screen);

            // despite the name, this updates everything EXCEPT for the screen, not including it
            void update();

            void log();
    };
}

#endif