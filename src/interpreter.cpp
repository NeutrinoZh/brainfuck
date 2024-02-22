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

void Interpreter::run(std::vector<Statement>& _program) {
    size_t brc;
    for (size_t it = 0; it < _program.size(); ++it) switch (_program[it].opCode) {
            case OPCODE::SET_ZERO:
                m_vm.memory[m_vm.pointer] = 0;
                std::cout << m_vm.pointer << ": pointer\n";
                break;
            case OPCODE::INC:
                m_vm.memory[m_vm.pointer] += _program[it].arg;
                break;
            case OPCODE::DEC:
                m_vm.memory[m_vm.pointer] -= _program[it].arg;
                break;
            case OPCODE::NEXT:
                m_vm.pointer += _program[it].arg;
                break;
            case OPCODE::PREV:
                m_vm.pointer -= _program[it].arg;
                break;
            case OPCODE::JMP_FW:
                if (m_vm.memory[m_vm.pointer] != 0) {
                    std::cout << m_vm.pointer << ": jmpfw pointer\n";
                    continue;
                }
                it = _program[it].arg;
                break;
            case OPCODE::JMP_BK:
                if (m_vm.memory[m_vm.pointer] == 0) {
                    std::cout << m_vm.pointer << ": jmpbk pointer\n";
                    continue;
                }
                it = _program[it].arg;
                break;
            case OPCODE::WRITE:
                std::cout << (int)m_vm.memory[m_vm.pointer];
                break;
            case OPCODE::READ:
                m_vm.memory[m_vm.pointer] = getchar();
                break;
            default:
                break;
        }
}

}  // namespace bf