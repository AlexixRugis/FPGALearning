#include "MifExport.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

namespace Compiler
{
    void saveMif(const std::string& filename, const std::vector<uint32_t>& program, size_t depth)
    {
        if (program.size() > depth)
            throw std::runtime_error("Program size exceeds specified depth");

        std::ofstream f(filename);
        if (!f)
            throw std::runtime_error("Cannot open file: " + filename);

        f << "WIDTH=32;\n";
        f << "DEPTH=" << depth << ";\n\n";

        f << "ADDRESS_RADIX=UNS;\n";
        f << "DATA_RADIX=HEX;\n\n";

        f << "CONTENT BEGIN\n";

        size_t i = 0;
        for (; i < program.size(); ++i)
        {
            f << std::dec << "    " << i << " : "
                << std::setw(8) << std::setfill('0') << std::hex << program[i]
                << ";\n";
        }

        if (i < depth)
        {
            f << std::dec << "    [" << i << ".." << (depth - 1) << "] : 00000000;\n";
        }

        f << "END;\n";
    }

};