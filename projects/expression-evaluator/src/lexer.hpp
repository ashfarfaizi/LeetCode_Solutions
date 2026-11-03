#pragma once

#include <stdexcept>
#include <string>
#include <vector>

namespace expr {

enum class TokenType { Number, Operator, LParen, RParen };

struct Token {
    TokenType type;
    double value = 0.0;  // valid when type == Number
    char op = '\0';      // valid when type == Operator

    bool operator==(const Token& o) const {
        return type == o.type && value == o.value && op == o.op;
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
// Throws ParseError on an unexpected character or malformed number.
std::vector<Token> tokenize(const std::string& input);

}  // namespace expr
