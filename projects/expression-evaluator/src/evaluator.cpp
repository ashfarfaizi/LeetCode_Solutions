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

double call(const std::string& name, double x) {
    if (name == "sqrt") {
        if (x < 0) throw EvalError("sqrt of negative number");
        return std::sqrt(x);
    }
    if (name == "ln" || name == "log10") {
        if (x <= 0) throw EvalError(name + " of non-positive number");
        return name == "ln" ? std::log(x) : std::log10(x);
    }
    if (name == "abs") return std::fabs(x);
    if (name == "exp") return std::exp(x);
    if (name == "sin") return std::sin(x);
    if (name == "cos") return std::cos(x);
    if (name == "tan") return std::tan(x);
    if (name == "floor") return std::floor(x);
    if (name == "ceil") return std::ceil(x);
    if (name == "round") return std::round(x);
    throw EvalError("unknown function '" + name + "'");
}

double lookup(const std::string& name) {
    if (name == "pi") return 3.14159265358979323846;
    if (name == "e") return 2.71828182845904523536;
    throw EvalError("unknown identifier '" + name + "'");
}
}  // namespace

double evaluateRPN(const std::vector<Token>& rpn) {
    std::vector<double> stack;
    for (const Token& t : rpn) {
        if (t.type == TokenType::Number) {
            stack.push_back(t.value);
            continue;
        }
        if (t.type == TokenType::Identifier) {
            stack.push_back(lookup(t.name));
            continue;
        }
        if (t.type == TokenType::Function) {
            if (stack.empty()) throw EvalError("malformed expression");
            stack.back() = call(t.name, stack.back());
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
