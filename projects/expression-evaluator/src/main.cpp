// Command-line front end.
//   calc "1 + 2 * 3"     evaluate the arguments as one expression and exit
//   calc --rpn "1 + 2"   print the expression in RPN instead of evaluating it
//   calc                 read expressions line by line from stdin (REPL)
//
// In the REPL, variables persist between lines ("x = 4", then "x * 2"),
// "ans" holds the last successful result, and "vars" lists the bindings.
#include <iostream>
#include <string>

#include "evaluator.hpp"
#include "parser.hpp"

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

bool printRPN(const std::string& line) {
    try {
        std::cout << expr::rpnToString(expr::toRPN(expr::tokenize(line))) << '\n';
        return true;
    } catch (const expr::ParseError& e) {
        std::cerr << "parse error: " << e.what() << '\n';
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
        int first = 1;
        bool rpnOnly = std::string(argv[1]) == "--rpn";
        if (rpnOnly) ++first;
        std::string expression;
        for (int i = first; i < argc; ++i) {
            if (i > first) expression += ' ';
            expression += argv[i];
        }
        bool ok = rpnOnly ? printRPN(expression) : evalAndPrint(expression, env);
        return ok ? 0 : 1;
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
