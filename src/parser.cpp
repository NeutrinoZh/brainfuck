#include "parser.h"
#include "opcodes.h"

namespace bf {

inline void pushStatement(std::vector<Statement>& _program, OPCODE _opCode) {
    if (_program.empty() || _program.back().opCode != _opCode)
        _program.push_back({_opCode, 1});
    else
        _program.back().arg += 1;
}

std::vector<Statement> Parser::parse(std::vector<char>& _rawInput) {
    size_t size = _rawInput.size();
    size_t pos = 0;
    
    std::vector<Statement> program;
    
    for (; pos < size; ++pos)
        switch (_rawInput[pos]) {
            case '+':
                pushStatement(program, OPCODE::INC);
                break;
            case '-':
                pushStatement(program, OPCODE::DEC);
                break;
            case '>':
                pushStatement(program, OPCODE::NEXT);
                break;
            case '<':
                pushStatement(program, OPCODE::PREV);
                break;
            case '[':
                program.push_back({OPCODE::JMP_FW, 0});
                break;
            case ']':
                program.push_back({OPCODE::JMP_BK, 0});
                break;
            case '.':
                program.push_back({OPCODE::WRITE, 0});
                break;
            case ',':
                program.push_back({OPCODE::READ, 0});
                break;
            default:
                break;
        }
        
    return program;
}

}