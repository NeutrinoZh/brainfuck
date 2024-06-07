#pragma once

#include "utils.h"
#include "statement.h"

namespace bf {
class Parser {
public:
    std::vector<Statement> parse(std::vector<char>& rawInput);    
};

}