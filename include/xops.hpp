#ifndef XOPS
#define XOPS

#include "xutils.hpp"

namespace xsef {
    void op0(void*, uint16_t);
    void op1(void*, uint16_t);
    void op2(void*, uint16_t);
    void op3(void*, uint16_t);
    
    void op4(void*, uint16_t);
    void op5(void*, uint16_t);
    void op6(void*, uint16_t);
    void op7(void*, uint16_t);
    
    void op8(void*, uint16_t);
    void op9(void*, uint16_t);
    void op10(void*, uint16_t);
    void op11(void*, uint16_t);
    
    void op12(void*, uint16_t);
    void op13(void*, uint16_t);
    void op14(void*, uint16_t);
    void op15(void*, uint16_t);

    // every operation needs an instance to the chip and the instruction (for x, y, n, nn, nnn)
    using fptr = void(*)(void*, uint16_t);

    // all operations 
    const std::array<fptr, 16> operations = {
        op0, op1, op2, op3,
        op4, op5, op6, op7,
        op8, op9, op10, op11,
        op12, op13, op14, op15
    };
}

#endif