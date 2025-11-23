#pragma once

#include <string>

namespace Compiler {

    class LabelGenerator
    {
    public:
        LabelGenerator(const std::string& p = "L") : prefix(p) {}

        std::string next()
        {
            return prefix + std::to_string(counter++);
        }

    private:
        size_t counter = 0;
        std::string prefix;
    };

};
