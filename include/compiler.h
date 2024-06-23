#pragma once

#include "statement.h"
#include "utils.h"

namespace bf {

class Compiler {
private:
public:
    void run(std::vector<Statement>& program);
};

}  // namespace bf