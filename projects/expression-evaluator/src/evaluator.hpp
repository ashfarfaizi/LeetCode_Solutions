#pragma once

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "lexer.hpp"

namespace expr {

class EvalError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Variable bindings, looked up before the built-in constants fail.
using Environment = std::map<std::string, double>;

// Evaluate an RPN token sequence with a value stack.
// Identifiers resolve to variables in env, then to the built-in constants
// pi and e. Built-in
// functions: sqrt abs exp ln log10 sin cos tan floor ceil round (one
// argument), pow hypot atan2 (two), min max (one or more).
// Throws EvalError on division or modulo by zero, an unknown identifier or function,
// a wrong argument count, a domain error such as sqrt(-1),
// or a malformed sequence.
double evaluateRPN(const std::vector<Token>& rpn, const Environment& env = {});

// Convenience: tokenize, convert to RPN and evaluate in one call.
double evaluate(const std::string& expression);

// Like evaluate(), but resolves identifiers from env and also accepts an
// assignment "name = expr", which stores the result in env and returns it.
// The constants pi and e cannot be reassigned.
double evaluate(const std::string& expression, Environment& env);

}  // namespace expr
