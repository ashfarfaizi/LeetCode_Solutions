#include "parser.hpp"

namespace expr {

namespace {
int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

bool rightAssociative(char op) { return op == '^'; }
}  // namespace

std::vector<Token> toRPN(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::vector<Token> ops;
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        const Token& t = tokens[i];
        switch (t.type) {
            case TokenType::Number:
                output.push_back(t);
                break;
            case TokenType::Operator:
                while (!ops.empty() && ops.back().type == TokenType::Operator) {
                    int top = precedence(ops.back().op), cur = precedence(t.op);
                    if (top > cur || (top == cur && !rightAssociative(t.op))) {
                        output.push_back(ops.back());
                        ops.pop_back();
                    } else {
                        break;
                    }
                }
                ops.push_back(t);
                break;
            case TokenType::LParen:
                ops.push_back(t);
                break;
            case TokenType::RParen:
                while (!ops.empty() && ops.back().type != TokenType::LParen) {
                    output.push_back(ops.back());
                    ops.pop_back();
                }
                if (ops.empty()) throw ParseError("unmatched ')'", i);
                ops.pop_back();  // discard '('
                break;
        }
    }
    while (!ops.empty()) {
        if (ops.back().type == TokenType::LParen)
            throw ParseError("unmatched '('", tokens.size());
        output.push_back(ops.back());
        ops.pop_back();
    }
    return output;
}

}  // namespace expr
