#pragma once

#include "opcodes.h"
#include "utils.h"

namespace bf {

class Interpreter {
private:
    struct VM {
        char* memory;
        int pointer;

        VM(size_t ram);
        ~VM();
    } m_vm;

public:
    Interpreter(size_t ram);

    void run(std::vector<OPCODE>& program);
};

}  // namespace bf