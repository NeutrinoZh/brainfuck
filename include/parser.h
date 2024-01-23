#pragma once

#include "utils.h"
#include "opcodes.h"

namespace bf {
class Parser {
public:
    std::vector<OPCODE> parse(std::vector<char>& rawInput);    
};

}