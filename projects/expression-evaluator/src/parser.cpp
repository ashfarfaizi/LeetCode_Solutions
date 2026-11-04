#include "parser.hpp"

#include <sstream>

namespace expr {

namespace {
int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': case '%': return 2;
        case 'u': return 3;  // unary minus: binds tighter than * / but looser than ^
        case '^': return 4;
        default: return 0;
    }
}

bool rightAssociative(char op) { return op == '^'; }
}  // namespace

std::vector<Token> toRPN(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::vector<Token> ops;
    // An operator is unary when nothing that can end an operand precedes it.
    bool expectOperand = true;
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        const Token& t = tokens[i];
        switch (t.type) {
            case TokenType::Identifier:
                if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::LParen) {
                    // Function call: the '(' is pushed on the next iteration and
                    // the function itself is emitted when its ')' closes.
                    ops.push_back({TokenType::Function, 1.0, '\0', t.name});
                    break;
                }
                output.push_back(t);
                expectOperand = false;
                break;
            case TokenType::Function:
                throw ParseError("unexpected function token", i);
            case TokenType::Assign:
                // Assignment is only valid as "name = expr" and is split off
                // by evaluate() before parsing.
                throw ParseError("unexpected '='", i);
            case TokenType::Number:
                output.push_back(t);
                expectOperand = false;
                break;
            case TokenType::Operator:
                if (expectOperand) {
                    if (t.op == '+') break;  // unary plus is a no-op
                    if (t.op != '-') throw ParseError(std::string("unexpected operator '") + t.op + "'", i);
                    // Prefix operators never pop: they apply to what follows.
                    ops.push_back({TokenType::Operator, 0.0, 'u'});
                    break;
                }
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
                expectOperand = true;
                break;
            case TokenType::LParen:
                ops.push_back(t);
                expectOperand = true;
                break;
            case TokenType::Comma: {
                // Flush the current argument, then count one more for the
                // function owning the innermost '('.
                while (!ops.empty() && ops.back().type != TokenType::LParen) {
                    output.push_back(ops.back());
                    ops.pop_back();
                }
                if (ops.size() < 2 || ops[ops.size() - 2].type != TokenType::Function)
                    throw ParseError("',' outside a function call", i);
                ops[ops.size() - 2].value += 1.0;
                expectOperand = true;
                break;
            }
            case TokenType::RParen:
                while (!ops.empty() && ops.back().type != TokenType::LParen) {
                    output.push_back(ops.back());
                    ops.pop_back();
                }
                if (ops.empty()) throw ParseError("unmatched ')'", i);
                ops.pop_back();  // discard '('
                if (!ops.empty() && ops.back().type == TokenType::Function) {
                    output.push_back(ops.back());
                    ops.pop_back();
                }
                expectOperand = false;
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

std::string rpnToString(const std::vector<Token>& rpn) {
    std::ostringstream out;
    for (std::size_t i = 0; i < rpn.size(); ++i) {
        if (i) out << ' ';
        const Token& t = rpn[i];
        switch (t.type) {
            case TokenType::Number: out << t.value; break;
            case TokenType::Identifier: out << t.name; break;
            case TokenType::Function:
                out << t.name;
                if (t.value != 1.0) out << '/' << static_cast<int>(t.value);
                break;
            case TokenType::Operator:
                if (t.op == 'u') out << "neg";
                else out << t.op;
                break;
            default: out << '?'; break;  // parens etc. never appear in RPN
        }
    }
    return out.str();
}

}  // namespace expr
