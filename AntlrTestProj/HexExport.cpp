#include "HexExport.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

namespace Compiler {

    void saveHex(const std::string& filename, const std::vector<uint32_t>& program, size_t depth) {
        if (program.size() > depth)
            throw std::runtime_error("Program size exceeds specified depth");

        std::ofstream f(filename);
        if (!f)
            throw std::runtime_error("Cannot open file: " + filename);

        f << "# Program begin\n\n";

        for (size_t i = 0; i < program.size(); ++i) {
            uint32_t word = program[i];
            uint32_t byte0 = (word & 0xFF);
            uint32_t byte1 = ((word >> 8) & 0xFF);
            uint32_t byte2 = ((word >> 16) & 0xFF);
            uint32_t byte3 = ((word >> 24) & 0xFF);

            f << std::setw(2) << std::setfill('0') << std::hex << byte0 << std::dec << " ";
            f << std::setw(2) << std::setfill('0') << std::hex << byte1 << std::dec << " ";
            f << std::setw(2) << std::setfill('0') << std::hex << byte2 << std::dec << " ";
            f << std::setw(2) << std::setfill('0') << std::hex << byte3 << std::dec << " ";
            f << "\n";
        }

        f << "\n\n# Program end";
    }

};