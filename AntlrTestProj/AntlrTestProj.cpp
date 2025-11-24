#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>

#include "antlr4-runtime.h"
#include "MyLanguageLexer.h"
#include "MyLanguageParser.h"
#include "MyLanguageBaseVisitor.h"

#include "MyVisitor.h"
#include "MifExport.h"

using namespace std;
using namespace antlr4;

void print_hex32(uint32_t v)
{
    std::cout << "0x"
        << std::hex << std::setw(8) << std::setfill('0')
        << v
        << std::dec;
}

int main()
{
    fstream ifs("input.myLang");
    
    ANTLRInputStream input(ifs);
    MyLanguageLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    MyLanguageParser parser(&tokens);

    tokens.fill();

    MyLanguageParser::ProgContext* tree = parser.prog();

    MyVisitor visitor;
    try
    {
        auto program = visitor.visitAll(tree);
        auto opcodes = std::get<0>(program);
        auto labels = std::get<1>(program);

        std::cout << opcodes.size() << std::endl;
        uint32_t addr = 0;
        size_t labelIndex = 0;
        for (auto instr : opcodes)
        {
            while (labelIndex < labels.size() && labels[labelIndex].second == addr)
            {
                std::cout << labels[labelIndex++].first << ":\n";
            }

            std::cout << std::setw(16) << std::setfill(' ') << addr << ' ';

            print_hex32(instr);
            std::cout << '\t' << Compiler::Assembler::disasm(instr) << '\n';

            addr++;
        }

        for (auto instr : opcodes)
        {
            print_hex32(instr);
            std::cout << ",\n";
        }

        Compiler::saveMif("output.mif", opcodes, 8192);
        std::cout << "Saved results to output.mif\n" << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "ERROR\n";
        std::cout << e.what() << std::endl;
    }

    return 0;
}