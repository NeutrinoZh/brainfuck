#include "parser.h"

namespace bf {

std::vector<OPCODE> Parser::parse(std::vector<char>& _rawInput) {
    size_t size = _rawInput.size();
    size_t pos = 0;
    
    std::vector<OPCODE> program;
    
    for (; pos < size; ++pos)
        switch (_rawInput[pos]) {
            case '+':
                program.push_back(OPCODE::INC);
                break;
            case '-':
                program.push_back(OPCODE::DEC);
                break;
            case '>':
                program.push_back(OPCODE::NEXT);
                break;
            case '<':
                program.push_back(OPCODE::PREV);
                break;
            case '[':
                program.push_back(OPCODE::JMP_FW);
                break;
            case ']':
                program.push_back(OPCODE::JMP_BK);
                break;
            case '.':
                program.push_back(OPCODE::WRITE);
                break;
            case ',':
                program.push_back(OPCODE::READ);
                break;
            default:
                break;
        }
        
    return program;
}

}