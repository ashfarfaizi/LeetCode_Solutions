// Command-line front end.
//   calc "1 + 2 * 3"     evaluate the arguments as one expression and exit
//   calc                 read expressions line by line from stdin (REPL)
//
// In the REPL, variables persist between lines ("x = 4", then "x * 2"),
// "ans" holds the last successful result, and "vars" lists the bindings.
#include <iostream>
#include <string>

#include "evaluator.hpp"

namespace {
bool evalAndPrint(const std::string& line, expr::Environment& env) {
    try {
        double result = expr::evaluate(line, env);
        env["ans"] = result;
        std::cout << result << '\n';
        return true;
    } catch (const expr::ParseError& e) {
        std::cerr << "parse error: " << e.what() << '\n';
    } catch (const expr::EvalError& e) {
        std::cerr << "eval error: " << e.what() << '\n';
    }
    return false;
}

std::string trim(const std::string& s) {
    auto b = s.find_first_not_of(" \t\r");
    if (b == std::string::npos) return "";
    auto e = s.find_last_not_of(" \t\r");
    return s.substr(b, e - b + 1);
}
}  // namespace

int main(int argc, char** argv) {
    expr::Environment env;
    if (argc > 1) {
        std::string expression;
        for (int i = 1; i < argc; ++i) {
            if (i > 1) expression += ' ';
            expression += argv[i];
        }
        return evalAndPrint(expression, env) ? 0 : 1;
    }

    std::string line;
    while (std::cout << "> " << std::flush, std::getline(std::cin, line)) {
        line = trim(line);
        if (line == "quit" || line == "exit") break;
        if (line.empty()) continue;
        if (line == "vars") {
            if (env.empty()) std::cout << "(no variables)\n";
            for (const auto& [name, value] : env) std::cout << name << " = " << value << '\n';
            continue;
        }
        evalAndPrint(line, env);
    }
    return 0;
}
