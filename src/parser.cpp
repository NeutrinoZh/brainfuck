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

    pos = 0;
    for (; pos < program.size(); ++pos) {
        if (program[pos].opCode == OPCODE::JMP_FW &&
            (program[pos + 1].opCode == OPCODE::INC || program[pos + 1].opCode == OPCODE::DEC) &&
            program[pos + 2].opCode == OPCODE::JMP_BK) {
            program[pos + 2].opCode = OPCODE::SET_ZERO;
            program.erase(program.begin() + pos);
            program.erase(program.begin() + pos);
        }
    }

    pos = 0;
    for (; pos < program.size(); ++pos)
        switch (program[pos].opCode) {
            case OPCODE::JMP_FW: {
                int it = pos;
                size_t brc = 1;
                while (brc) {
                    ++it;
                    if (it > program.size())
                        std::cerr << "index out of range:" << it << "\n";
                    if (program[it].opCode == OPCODE::JMP_FW)
                        ++brc;
                    if (program[it].opCode == OPCODE::JMP_BK)
                        --brc;
                }

                program[pos].arg = it;
                break;
            }
            case OPCODE::JMP_BK: {
                size_t brc = 1;
                int it = pos;

                while (brc) {
                    --it;
                    if (it < 0)
                        std::cerr << "index out of range: " << it << "; pos: " << pos << "\n";
                    if (program[it].opCode == OPCODE::JMP_FW)
                        --brc;
                    if (program[it].opCode == OPCODE::JMP_BK)
                        ++brc;
                }

                program[pos].arg = it;
                break;
            }
            default:
                break;
        }
    
    return program;
}

}