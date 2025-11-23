#pragma once

#include <vector>

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

        void compileCJmp();

        void setConst(uint32_t addr, uint32_t val)
        {
            mProgram[addr] = val;
        }

        uint32_t getOpAddr() const
        {
            return mProgram.size();
        }

        std::vector<Assembler::opcode_t> getProgram() const
        {
            return mProgram;
        }
    private:
        Assembler mAsm;
        std::vector<Assembler::opcode_t> mProgram;
    };
};
