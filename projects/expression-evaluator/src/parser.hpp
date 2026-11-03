#pragma once

#include <vector>

#include "lexer.hpp"

namespace expr {

// Convert infix tokens to Reverse Polish Notation using Dijkstra's
// shunting-yard algorithm. Precedence (low to high): + -, * /, ^.
// ^ is right-associative; the rest are left-associative.
// Throws ParseError on mismatched parentheses.
std::vector<Token> toRPN(const std::vector<Token>& tokens);

}  // namespace expr
