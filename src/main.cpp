#include "interpreter.h"
#include "parser.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: $ brainfuck [source]" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1], std::ios_base::binary);
    if (!file.is_open()) {
        std::cerr << "File " << argv[1] << " not found" << std::endl;
        return EXIT_FAILURE;
    }

    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    file.read(buffer.data(), size);

    file.close();

    bf::Parser parser;
    auto program = parser.parse(buffer);
    
    bf::Interpreter interpreter(10000);
    interpreter.run(program);

    return EXIT_SUCCESS;
}