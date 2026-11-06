#include "lexer.hpp"

#include <cctype>
#include <cstdlib>

namespace expr {

namespace {
bool isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}
// Map "<=", ">=", "==", "!=" to their single-char codes; 0 if not one.
char twoCharOperator(char a, char b) {
    if (b != '=') return '\0';
    switch (a) {
        case '<': return 'l';
        case '>': return 'g';
        case '=': return 'E';
        case '!': return 'N';
        default: return '\0';
    }
}
}  // namespace

std::string operatorText(char op) {
    switch (op) {
        case 'l': return "<=";
        case 'g': return ">=";
        case 'E': return "==";
        case 'N': return "!=";
        case 'u': return "neg";
        default: return std::string(1, op);
    }
}

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
        } else if (char two = i + 1 < input.size() ? twoCharOperator(c, input[i + 1]) : '\0') {
            tokens.push_back({TokenType::Operator, 0.0, two});
            i += 2;
        } else if (c == '<' || c == '>' || c == '!') {
            tokens.push_back({TokenType::Operator, 0.0, c});
            ++i;
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
