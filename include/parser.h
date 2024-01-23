#pragma once
#include <vector>
#include "utils.h"

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

class Parser {
public:
    std::vector<OPCODE> parse(std::vector<char>& rawInput);    
};

}