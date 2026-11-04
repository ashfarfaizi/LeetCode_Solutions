#pragma once

#include <vector>

#include "lexer.hpp"

namespace expr {

// Convert infix tokens to Reverse Polish Notation using Dijkstra's
// shunting-yard algorithm. Precedence (low to high): + -, * / %, unary -, ^.
// ^ is right-associative; the binary rest are left-associative.
// Unary minus is emitted as an Operator token with op == 'u', so -2^2 == -4
// and 2^-1 == 0.5. A leading or post-operator '+' is accepted and dropped.
// Throws ParseError on mismatched parentheses or a misplaced operator.
std::vector<Token> toRPN(const std::vector<Token>& tokens);

}  // namespace expr
