#pragma once

#include <vector>
#include <unordered_map>

#include "Types.h"
#include "Assembler.h"

namespace Compiler
{
    class CodeGenerator
    {
    public:
        void compileAdd();
        void compileSub();
        void compileMul();
        void compileDiv();
        void compileRem();
        void compileAnd();
        void compileOr();
        void compileXor();
        void compileNot();
        void compileShl();
        void compileShr();
        void compileEq();
        void compileLt();

        void compileConst(uint32_t val);
        void compileLoad(addr_t addr);
        void compileSave(addr_t addr);

        void compileCJmpz();
        void compileAJmp();

        void declareLabel(const std::string& labelName);
        void compileRef(const std::string& labelName);
        void resolveRefs();

        std::vector<Assembler::opcode_t> getProgram() const
        {
            return mProgram;
        }
    private:
        Assembler mAsm;
        std::vector<Assembler::opcode_t> mProgram;
        std::unordered_map<std::string, size_t> mLabels;
        std::unordered_map<std::string, std::vector<size_t>> mRefs;
    };
};
