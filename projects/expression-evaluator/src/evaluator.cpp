#include "evaluator.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>

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

void expectArgs(const std::string& name, std::size_t got, std::size_t want) {
    if (got != want)
        throw EvalError(name + "() takes " + std::to_string(want) + " argument" +
                        (want == 1 ? "" : "s") + ", got " + std::to_string(got));
}

double call(const std::string& name, const std::vector<double>& args) {
    if (name == "min" || name == "max") {
        if (args.empty()) throw EvalError(name + "() needs at least one argument");
        return name == "min" ? *std::min_element(args.begin(), args.end())
                             : *std::max_element(args.begin(), args.end());
    }
    if (name == "pow" || name == "hypot" || name == "atan2") {
        expectArgs(name, args.size(), 2);
        if (name == "pow") return std::pow(args[0], args[1]);
        if (name == "hypot") return std::hypot(args[0], args[1]);
        return std::atan2(args[0], args[1]);
    }

    static const char* const unary[] = {"sqrt", "ln",  "log10", "abs",  "exp",  "sin",
                                        "cos",  "tan", "floor", "ceil", "round"};
    if (std::find(std::begin(unary), std::end(unary), name) == std::end(unary))
        throw EvalError("unknown function '" + name + "'");
    expectArgs(name, args.size(), 1);
    double x = args[0];
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
    return std::round(x);
}

bool isConstant(const std::string& name) { return name == "pi" || name == "e"; }

double lookup(const std::string& name, const Environment& env) {
    auto it = env.find(name);
    if (it != env.end()) return it->second;
    if (name == "pi") return 3.14159265358979323846;
    if (name == "e") return 2.71828182845904523536;
    throw EvalError("unknown identifier '" + name + "'");
}
}  // namespace

double evaluateRPN(const std::vector<Token>& rpn, const Environment& env) {
    std::vector<double> stack;
    for (const Token& t : rpn) {
        if (t.type == TokenType::Number) {
            stack.push_back(t.value);
            continue;
        }
        if (t.type == TokenType::Identifier) {
            stack.push_back(lookup(t.name, env));
            continue;
        }
        if (t.type == TokenType::Function) {
            auto argc = static_cast<std::size_t>(t.value);
            if (stack.size() < argc) throw EvalError("malformed expression");
            std::vector<double> args(stack.end() - static_cast<std::ptrdiff_t>(argc), stack.end());
            stack.resize(stack.size() - argc);
            stack.push_back(call(t.name, args));
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
    Environment scratch;
    return evaluate(expression, scratch);
}

double evaluate(const std::string& expression, Environment& env) {
    std::vector<Token> tokens = tokenize(expression);
    if (tokens.size() >= 2 && tokens[0].type == TokenType::Identifier &&
        tokens[1].type == TokenType::Assign) {
        const std::string name = tokens[0].name;
        if (isConstant(name)) throw EvalError("cannot assign to constant '" + name + "'");
        tokens.erase(tokens.begin(), tokens.begin() + 2);
        double value = evaluateRPN(toRPN(tokens), env);
        env[name] = value;  // only stored once evaluation succeeded
        return value;
    }
    return evaluateRPN(toRPN(tokens), env);
}

}  // namespace expr
