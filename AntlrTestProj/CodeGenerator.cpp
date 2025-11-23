#include "CodeGenerator.h"

namespace Compiler
{
    void CodeGenerator::compileAdd()
    {
        mProgram.push_back(mAsm.add());
    }

    void CodeGenerator::compileSub()
    {
        mProgram.push_back(mAsm.sub());
    }

    void CodeGenerator::compileMul()
    {
        mProgram.push_back(mAsm.mul());
    }

    void CodeGenerator::compileDiv()
    {
        mProgram.push_back(mAsm.div());
    }

    void CodeGenerator::compileRem()
    {
        mProgram.push_back(mAsm.rem());
    }

    void CodeGenerator::compileAnd()
    {
        mProgram.push_back(mAsm.and_());
    }

    void CodeGenerator::compileOr()
    {
        mProgram.push_back(mAsm.or_());
    }

    void CodeGenerator::compileXor()
    {
        mProgram.push_back(mAsm.xor_());
    }

    void CodeGenerator::compileNot()
    {
        mProgram.push_back(mAsm.not_());
    }

    void CodeGenerator::compileShl()
    {
        mProgram.push_back(mAsm.shl());
    }

    void CodeGenerator::compileShr()
    {
        mProgram.push_back(mAsm.shr());
    }

    void CodeGenerator::compileEq()
    {
        mProgram.push_back(mAsm.equ());
    }

    void CodeGenerator::compileLt()
    {
        mProgram.push_back(mAsm.lt());
    }

    void CodeGenerator::compileConst(uint32_t val)
    {
        mProgram.push_back(mAsm.lconst(val));
    }

    void CodeGenerator::compileLoad(addr_t addr)
    {
        mProgram.push_back(mAsm.lconst(addr));
        mProgram.push_back(mAsm.lmem());
    }

    void CodeGenerator::compileSave(addr_t addr)
    {
        mProgram.push_back(mAsm.lconst(addr));
        mProgram.push_back(mAsm.stmem());
    }

    void CodeGenerator::compileCJmpz()
    {
        mProgram.push_back(mAsm.cjmpz());
    }

    void CodeGenerator::compileAJmp()
    {
        mProgram.push_back(mAsm.ajmp());
    }

    void CodeGenerator::declareLabel(const std::string& labelName)
    {
        if (mLabels.contains(labelName))
        {
            throw std::runtime_error(__FUNCTION__ ": label with name \'" + labelName + "\' already declared");
        }

        mLabels[labelName] = mProgram.size();
    }

    void CodeGenerator::compileRef(const std::string& labelName)
    {
        mRefs[labelName].push_back(mProgram.size());
        mProgram.push_back(mAsm.lconst(0));
    }

    void CodeGenerator::resolveRefs()
    {
        for (const auto& [labelName, poses] : mRefs)
        {
            auto iter = mLabels.find(labelName);
            if (iter == mLabels.end())
            {
                throw std::runtime_error(__FUNCTION__ ": label with name \'" + labelName + "\' is not declared");
            }

            for (auto pos : poses)
            {
                mProgram[pos] = mAsm.lconst(iter->second);
            }
        }
    }
};