#include "VariableAllocator.h"

#include <stdexcept>
#include <iostream>

namespace Compiler
{
    void VariableAllocator::startBlock()
    {
        mBlocks.emplace_back();
    }

    void VariableAllocator::endBlock()
    {
        if (mBlocks.size() <= 1)
        {
            throw std::runtime_error(__FUNCTION__ ": there are no blocks to close.");
        }

        const auto& block = mBlocks.back();

        for (const auto& [ident, addr] : block.variables)
        {
            freeAddr(addr);
        }

        mBlocks.pop_back();
    }

    addr_t VariableAllocator::alloc(const ident_t & name)
    {
        auto& block = mBlocks.back();

        if (block.variables.contains(name))
        {
            throw std::runtime_error(__FUNCTION__ ": variable is already declared.");
        }

        auto addr = allocAddr();
        block.variables[name] = addr;

        std::cout << "Allocated var \'" << name << "'\ to addr " << addr << std::endl;

        return mBaseOffset + addr;
    }

    std::optional<addr_t> VariableAllocator::getAddr(const ident_t& name) const
    {
        for (auto blockIt = mBlocks.rbegin(); blockIt != mBlocks.rend(); ++blockIt)
        {
            auto varIt = blockIt->variables.find(name);

            if (varIt != blockIt->variables.end())
            {
                return mBaseOffset + varIt->second;
            }
        }

        return std::nullopt;
    }

    addr_t VariableAllocator::allocAddr()
    {
        if (!mFree.empty())
        {
            auto addr = mFree.back();
            mFree.pop_back();
            return addr;
        }
        else
        {
            return mFirstFree++;
        }
    }

    void VariableAllocator::freeAddr(addr_t addr)
    {
        mFree.push_back(addr);
    }
}