#pragma once
#include "opcodes.h"

namespace bf {

struct Statement {
    OPCODE opCode;
    int arg; 
};

}