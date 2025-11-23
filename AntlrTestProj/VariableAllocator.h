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
        enum Scope
        {
            GLOBAL,
            STACK
        };

        VariableAllocator(addr_t baseOffset, Scope scope) : mBaseOffset(baseOffset), mScope(scope)
        {
            startBlock();
        }

        void startBlock();
        void endBlock();

        addr_t alloc(const ident_t& name);
        std::optional<addr_t> getAddr(const ident_t& name) const;

        Scope getScope() const
        {
            return mScope;
        }

        addr_t getMaxAlloc() const
        {
            return mFirstFree;
        }

    private:
        struct Block
        {
            std::unordered_map<ident_t, addr_t> variables;
        };

        Scope mScope;
        addr_t mBaseOffset;
        addr_t mFirstFree = 0;
        std::vector<addr_t> mFree;
        std::vector<Block> mBlocks;

        addr_t allocAddr();
        void freeAddr(addr_t addr);
    };
}