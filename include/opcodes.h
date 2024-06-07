#pragma once

namespace bf {

enum class OPCODE {
    INC, // 0
    DEC, // 1

    NEXT, // 2
    PREV, // 3

    JMP_FW, // 4
    JMP_BK, // 5

    WRITE, // 6
    READ,  // 7

    SET_ZERO, // 8
};

}