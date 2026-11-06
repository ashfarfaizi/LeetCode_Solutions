#include "lexer.hpp"

#include <cctype>
#include <cstdlib>

namespace expr {

namespace {
bool isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}
}  // namespace

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::size_t i = 0;
    while (i < input.size()) {
        char c = input[i];
        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
        } else if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            std::size_t start = i;
            bool seenDot = false;
            while (i < input.size() &&
                   (std::isdigit(static_cast<unsigned char>(input[i])) || input[i] == '.')) {
                if (input[i] == '.') {
                    if (seenDot) throw ParseError("malformed number", i);
                    seenDot = true;
                }
                ++i;
            }
            if (i - start == 1 && input[start] == '.') throw ParseError("malformed number", start);
            // Optional exponent: e/E, an optional sign, then at least one digit.
            // "2e" or "2ex" is left alone so the 'e' lexes as an identifier.
            if (i < input.size() && (input[i] == 'e' || input[i] == 'E')) {
                std::size_t j = i + 1;
                if (j < input.size() && (input[j] == '+' || input[j] == '-')) ++j;
                if (j < input.size() && std::isdigit(static_cast<unsigned char>(input[j]))) {
                    while (j < input.size() && std::isdigit(static_cast<unsigned char>(input[j]))) ++j;
                    i = j;
                }
            }
            std::string text = input.substr(start, i - start);
            tokens.push_back({TokenType::Number, std::strtod(text.c_str(), nullptr), '\0'});
        } else if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            std::size_t start = i;
            while (i < input.size() &&
                   (std::isalnum(static_cast<unsigned char>(input[i])) || input[i] == '_'))
                ++i;
            tokens.push_back({TokenType::Identifier, 0.0, '\0', input.substr(start, i - start)});
        } else if (isOperatorChar(c)) {
            tokens.push_back({TokenType::Operator, 0.0, c});
            ++i;
        } else if (c == '(') {
            tokens.push_back({TokenType::LParen, 0.0, '\0'});
            ++i;
        } else if (c == '=') {
            tokens.push_back({TokenType::Assign, 0.0, '\0'});
            ++i;
        } else if (c == ',') {
            tokens.push_back({TokenType::Comma, 0.0, '\0'});
            ++i;
        } else if (c == ')') {
            tokens.push_back({TokenType::RParen, 0.0, '\0'});
            ++i;
        } else {
            throw ParseError(std::string("unexpected character '") + c + "'", i);
        }
    }
    return tokens;
}

}  // namespace expr
