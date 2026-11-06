#pragma once

#include <stdexcept>
#include <string>
#include <vector>

namespace expr {

// Function tokens are never produced by the lexer: the parser turns an
// Identifier followed by '(' into a Function whose value holds its arity.
enum class TokenType { Number, Operator, LParen, RParen, Comma, Assign, Identifier, Function };

struct Token {
    TokenType type;
    double value = 0.0;  // Number: the value; Function: argument count
    char op = '\0';      // valid when type == Operator
    std::string name{};  // valid when type == Identifier or Function

    bool operator==(const Token& o) const {
        return type == o.type && value == o.value && op == o.op && name == o.name;
    }
};

class ParseError : public std::runtime_error {
public:
    ParseError(const std::string& msg, std::size_t pos)
        : std::runtime_error(msg + " at position " + std::to_string(pos)), pos_(pos) {}
    std::size_t position() const { return pos_; }

private:
    std::size_t pos_;
};

// Split an expression into tokens. Whitespace is ignored.
// Numbers may use scientific notation (1e3, 2.5E-4, .5e+2).
// Identifiers match [A-Za-z_][A-Za-z0-9_]*.
// Throws ParseError on an unexpected character or malformed number.
std::vector<Token> tokenize(const std::string& input);

}  // namespace expr
