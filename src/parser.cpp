#include "parser.h"

namespace bf {

std::vector<OPCODE> Parser::parse(std::vector<char>& _rawInput) {
    size_t size = _rawInput.size();
    size_t pos = 0;
    
    std::vector<OPCODE> program(size);
    
    for (; pos < size; ++pos)
        switch (_rawInput[pos]) {
            case '+':
                program[pos] = OPCODE::INC;
                break;
            case '-':
                program[pos] = OPCODE::DEC;
                break;
            case '>':
                program[pos] = OPCODE::NEXT;
                break;
            case '<':
                program[pos] = OPCODE::PREV;
                break;
            case '[':
                program[pos] = OPCODE::JMP_FW;
                break;
            case ']':
                program[pos] = OPCODE::JMP_BK;
                break;
            default:
                break;
        }
        
    return program;
}

}