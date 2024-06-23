#include "compiler.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <memory>

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/Support/TargetSelect.h"
#include "opcodes.h"
#include "statement.h"

namespace bf {

void Compiler::run(std::vector<Statement> &program) {
    llvm::LLVMContext context;
    llvm::Module module("my_module", context);
    llvm::IRBuilder<> builder(context);

    llvm::FunctionType *mainFuncType =
        llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);

    llvm::Function *mainFunc =
        llvm::Function::Create(mainFuncType, llvm::Function::ExternalLinkage, "main", &module);

    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);

    llvm::ConstantInt *one = llvm::ConstantInt::get(context, llvm::APInt(32, 1));

    auto ar_type = llvm::ArrayType::get(llvm::Type::getInt32Ty(context), 1000);
    llvm::AllocaInst *ram = builder.CreateAlloca(ar_type, nullptr, "ram");

    auto ptr_type = llvm::Type::getInt32Ty(context);
    llvm::AllocaInst *ptr = builder.CreateAlloca(ptr_type, nullptr, "ptr");

    std::vector<llvm::Type *> putsArgs = {llvm::Type::getInt32Ty(context)};
    llvm::FunctionType *putsType =
        llvm::FunctionType::get(llvm::Type::getInt32Ty(context), putsArgs, false);
    llvm::Function *putsFunc =
        llvm::Function::Create(putsType, llvm::Function::ExternalLinkage, "puts", &module);

    for (auto &statement : program) {
        switch (statement.opCode) {
            case OPCODE::INC: {
                llvm::Value *ptrValue = builder.CreateLoad(ptr_type, ptr);
                llvm::Value *indices[] = {
                    llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0), ptrValue};
                llvm::Value *elementPtr = builder.CreateGEP(ar_type, ram, indices);

                llvm::Value *currentValue =
                    builder.CreateLoad(llvm::Type::getInt32Ty(context), elementPtr);

                llvm::Value *newValue = builder.CreateAdd(currentValue, one);

                builder.CreateStore(newValue, elementPtr);

                break;
            }
            case OPCODE::WRITE: {
                llvm::Value *ptrValue = builder.CreateLoad(ptr_type, ptr);
                builder.CreateCall(putsFunc, {ptrValue}, "putscall");
            }
            default:
                break;
        }
    }

    builder.CreateRetVoid();

    llvm::verifyFunction(*mainFunc);

    llvm::legacy::PassManager pass;
    pass.run(module);

    module.print(llvm::outs(), nullptr);

    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    auto jit = llvm::cantFail(llvm::orc::LLJITBuilder().create());
    auto threadSafeModule = llvm::orc::ThreadSafeModule(std::make_unique(module), std
                                                        : make_unique(context));
}

}  // namespace bf