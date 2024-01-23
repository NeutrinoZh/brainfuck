#pragma once

namespace bf {

enum class OPCODE {
    INC,
    DEC,

    NEXT,
    PREV,

    JMP_FW,
    JMP_BK,
        
    WRITE,
    READ,
};

}