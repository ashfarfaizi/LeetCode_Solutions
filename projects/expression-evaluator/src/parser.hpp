#pragma once

#include <vector>

#include "lexer.hpp"

namespace expr {

// Convert infix tokens to Reverse Polish Notation using Dijkstra's
// shunting-yard algorithm. Precedence (low to high): + -, * / %, unary -, ^.
// ^ is right-associative; the binary rest are left-associative.
// Unary minus is emitted as an Operator token with op == 'u', so -2^2 == -4
// and 2^-1 == 0.5. A leading or post-operator '+' is accepted and dropped.
// An identifier directly followed by '(' is a function call; it is emitted
// as a Function token after its arguments, e.g. "sqrt(x + 1)" -> "x 1 + sqrt"
// and "max(1, 2)" -> "1 2 max"; the token's value is the argument count.
// Throws ParseError on mismatched parentheses, a misplaced operator, or a
// comma outside a function call.
std::vector<Token> toRPN(const std::vector<Token>& tokens);

}  // namespace expr
