#include "evaluator.hpp"

#include <cmath>

#include "parser.hpp"

namespace expr {

namespace {
double apply(char op, double a, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0.0) throw EvalError("division by zero");
            return a / b;
        case '%':
            if (b == 0.0) throw EvalError("modulo by zero");
            return std::fmod(a, b);  // result takes the sign of a, like C++ %
        case '^': return std::pow(a, b);
    }
    throw EvalError(std::string("unknown operator '") + op + "'");
}
}  // namespace

double evaluateRPN(const std::vector<Token>& rpn) {
    std::vector<double> stack;
    for (const Token& t : rpn) {
        if (t.type == TokenType::Number) {
            stack.push_back(t.value);
            continue;
        }
        if (t.type == TokenType::Operator && t.op == 'u' && !stack.empty()) {
            stack.back() = -stack.back();
            continue;
        }
        if (t.type != TokenType::Operator || stack.size() < 2)
            throw EvalError("malformed expression");
        double b = stack.back(); stack.pop_back();
        double a = stack.back(); stack.pop_back();
        stack.push_back(apply(t.op, a, b));
    }
    if (stack.size() != 1) throw EvalError("malformed expression");
    return stack.back();
}

double evaluate(const std::string& expression) {
    return evaluateRPN(toRPN(tokenize(expression)));
}

}  // namespace expr
