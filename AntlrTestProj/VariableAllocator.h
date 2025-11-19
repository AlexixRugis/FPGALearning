#pragma once

#include <vector>
#include <cstddef>
#include <string>
#include <optional>
#include <unordered_map>

#include "Types.h"

namespace Compiler
{
    class VariableAllocator final
    {
    public:
        VariableAllocator(addr_t baseOffset) : mBaseOffset(baseOffset)
        {
            startBlock();
        }

        void startBlock();
        void endBlock();

        addr_t alloc(const ident_t& name);
        std::optional<addr_t> getAddr(const ident_t& name) const;

    private:
        struct Block
        {
            std::unordered_map<ident_t, addr_t> variables;
        };

        addr_t mBaseOffset;
        addr_t mFirstFree;
        std::vector<addr_t> mFree;
        std::vector<Block> mBlocks;

        addr_t allocAddr();
        void freeAddr(addr_t addr);
    };
}