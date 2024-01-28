#include "interpreter.h"

#include <cstdio>

#include "opcodes.h"

namespace bf {

Interpreter::VM::VM(size_t _ram) {
    pointer = 0;

    memory = new char[_ram];
    std::fill(memory, memory + _ram, 0);
}

Interpreter::VM::~VM() {
    delete[] memory;
}

Interpreter::Interpreter(size_t _ram) : m_vm(_ram) {
}

void Interpreter::run(std::vector<OPCODE>& _program) {
    size_t brc;
    for (size_t it = 0; it < _program.size(); ++it) switch (_program[it]) {
            case OPCODE::INC:
                ++m_vm.memory[m_vm.pointer];
                break;
            case OPCODE::DEC:
                --m_vm.memory[m_vm.pointer];
                break;
            case OPCODE::NEXT:
                ++m_vm.pointer;
                break;
            case OPCODE::PREV:
                --m_vm.pointer;
                break;
            case OPCODE::JMP_FW:
                if (m_vm.memory[m_vm.pointer] != 0)
                    continue;

                brc = 1;
                while (brc) {
                    ++it;
                    if (_program[it] == OPCODE::JMP_FW)
                        ++brc;
                    if (_program[it] == OPCODE::JMP_BK)
                        --brc;
                }

                break;
            case OPCODE::JMP_BK:
                if (m_vm.memory[m_vm.pointer] == 0)
                    continue;

                brc = 1;
                while (brc) {
                    --it;
                    if (_program[it] == OPCODE::JMP_FW)
                        --brc;
                    if (_program[it] == OPCODE::JMP_BK)
                        ++brc;
                }

                //--it;

                break;
            case OPCODE::WRITE:
                std::cout << m_vm.memory[m_vm.pointer];
                break;
            case OPCODE::READ:
                m_vm.memory[m_vm.pointer] = getchar();
                break;
            default:
                break;
        }
}

}  // namespace bf