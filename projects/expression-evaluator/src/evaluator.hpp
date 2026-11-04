#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "lexer.hpp"

namespace expr {

class EvalError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Evaluate an RPN token sequence with a value stack.
// Identifiers resolve to the built-in constants pi and e.
// Throws EvalError on division or modulo by zero, an unknown identifier,
// or a malformed sequence.
double evaluateRPN(const std::vector<Token>& rpn);

// Convenience: tokenize, convert to RPN and evaluate in one call.
double evaluate(const std::string& expression);

}  // namespace expr
