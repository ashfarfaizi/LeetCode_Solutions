#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "json_tokenizer.hpp"

namespace jt {

// Thrown when the tokens are individually valid but do not form a JSON value.
class SyntaxError : public TokenizeError {
public:
    SyntaxError(const std::string& msg, const Token& at)
        : TokenizeError(msg, at.offset, at.line, at.column) {}
};

// Checks that src is exactly one JSON value (RFC 8259 grammar) surrounded by
// optional whitespace. Uses an explicit stack, so deeply nested input cannot
// overflow the call stack; max_depth bounds nesting (0 = unlimited).
// Throws TokenizeError / SyntaxError describing the first problem.
inline void validate(std::string_view src, std::size_t max_depth = 0) {
    enum class Ctx { Array, Object };
    // What the parser expects next.
    enum class Want { Value, ValueOrClose, CommaOrClose, Key, KeyOrClose, Colon };

    Tokenizer lexer(src);
    std::vector<Ctx> stack;
    Want want = Want::Value;
    bool done = false;

    auto describe = [](const Token& t) {
        return t.type == TokenType::End ? std::string("end of input")
                                        : std::string("'") + t.value + "'";
    };

    for (Token tok = lexer.next();; tok = lexer.next()) {
        if (done) {
            if (tok.type != TokenType::End)
                throw SyntaxError("unexpected " + describe(tok) + " after top-level value", tok);
            return;
        }
        bool closes_array = tok.type == TokenType::RBracket && !stack.empty() && stack.back() == Ctx::Array;
        bool closes_object = tok.type == TokenType::RBrace && !stack.empty() && stack.back() == Ctx::Object;
        auto after_value = [&] {
            if (stack.empty()) done = true;
            else want = Want::CommaOrClose;
        };

        switch (want) {
            case Want::Value:
            case Want::ValueOrClose:
                if (want == Want::ValueOrClose && closes_array) {
                    stack.pop_back();
                    after_value();
                    break;
                }
                switch (tok.type) {
                    case TokenType::LBracket:
                    case TokenType::LBrace:
                        stack.push_back(tok.type == TokenType::LBracket ? Ctx::Array : Ctx::Object);
                        if (max_depth && stack.size() > max_depth)
                            throw SyntaxError("nesting deeper than " + std::to_string(max_depth), tok);
                        want = tok.type == TokenType::LBracket ? Want::ValueOrClose : Want::KeyOrClose;
                        break;
                    case TokenType::String:
                    case TokenType::Number:
                    case TokenType::True:
                    case TokenType::False:
                    case TokenType::Null:
                        after_value();
                        break;
                    default:
                        throw SyntaxError("expected a value but found " + describe(tok), tok);
                }
                break;
            case Want::CommaOrClose:
                if (tok.type == TokenType::Comma) {
                    want = stack.back() == Ctx::Array ? Want::Value : Want::Key;
                } else if (closes_array || closes_object) {
                    stack.pop_back();
                    after_value();
                } else {
                    throw SyntaxError(std::string("expected ',' or '") +
                                          (stack.back() == Ctx::Array ? "]" : "}") + "' but found " +
                                          describe(tok),
                                      tok);
                }
                break;
            case Want::Key:
            case Want::KeyOrClose:
                if (want == Want::KeyOrClose && closes_object) {
                    stack.pop_back();
                    after_value();
                } else if (tok.type == TokenType::String) {
                    want = Want::Colon;
                } else {
                    throw SyntaxError("expected a string key but found " + describe(tok), tok);
                }
                break;
            case Want::Colon:
                if (tok.type != TokenType::Colon)
                    throw SyntaxError("expected ':' but found " + describe(tok), tok);
                want = Want::Value;
                break;
        }
    }
}

// Non-throwing convenience wrapper; stores the error message when invalid.
inline bool is_valid(std::string_view src, std::string* error = nullptr) {
    try {
        validate(src);
        return true;
    } catch (const TokenizeError& e) {
        if (error) *error = e.what();
        return false;
    }
}

}  // namespace jt
