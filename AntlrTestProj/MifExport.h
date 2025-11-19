#pragma once

#include <vector>
#include <string>

namespace Compiler
{
    void saveMif(const std::string& filename, const std::vector<uint32_t>& program, size_t depth);
};