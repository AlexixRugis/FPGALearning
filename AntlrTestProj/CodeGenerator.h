#pragma once

#include <algorithm>
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
        void compileStackLoad(addr_t addr);
        void compileSave(addr_t addr);
        void compileStackSave(addr_t addr);

        void compilePushPpc();
        void compileCJmpz();
        void compileAJmp();

        void compileLoadFp();
        void compilePrologue();
        void compileEpilogue(uint32_t frameSize);

        void declareLabel(const std::string& labelName);
        void compileRef(const std::string& labelName);
        void resolveRefs();

        std::vector<Assembler::opcode_t> getProgram() const
        {
            return mProgram;
        }

        std::vector<std::pair<std::string, size_t>> getLabels() const
        {
            std::vector<std::pair<std::string, size_t>> labels(mLabels.begin(), mLabels.end());

            std::sort(labels.begin(), labels.end(), [](const std::pair<std::string, size_t>& l, const std::pair<std::string, size_t>& r)
                {
                    if (l.second == r.second)
                    {
                        return l.first < r.first;
                    }

                    return l.second < r.second;
                });

            return labels;
        }
    private:
        Assembler mAsm;
        std::vector<Assembler::opcode_t> mProgram;
        std::unordered_map<std::string, size_t> mLabels;
        std::unordered_map<std::string, std::vector<size_t>> mRefs;
        std::vector<size_t> mFpAdds;
    };
};
