// Command-line front end.
//   calc "1 + 2 * 3"     evaluate the arguments as one expression and exit
//   calc                 read expressions line by line from stdin (REPL)
#include <iostream>
#include <string>

#include "evaluator.hpp"

namespace {
bool evalAndPrint(const std::string& line) {
    try {
        std::cout << expr::evaluate(line) << '\n';
        return true;
    } catch (const expr::ParseError& e) {
        std::cerr << "parse error: " << e.what() << '\n';
    } catch (const expr::EvalError& e) {
        std::cerr << "eval error: " << e.what() << '\n';
    }
    return false;
}
}  // namespace

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string expression;
        for (int i = 1; i < argc; ++i) {
            if (i > 1) expression += ' ';
            expression += argv[i];
        }
        return evalAndPrint(expression) ? 0 : 1;
    }

    std::string line;
    while (std::cout << "> " << std::flush, std::getline(std::cin, line)) {
        if (line == "quit" || line == "exit") break;
        if (line.find_first_not_of(" \t") == std::string::npos) continue;
        evalAndPrint(line);
    }
    return 0;
}
