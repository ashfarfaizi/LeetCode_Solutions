#pragma once

#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

#include "json_tokenizer.hpp"
#include "json_validate.hpp"

namespace jt {

// Encodes a decoded string value as a JSON string literal, quotes included.
// Only '"', '\\' and control characters are escaped (using the short forms
// where JSON has one); other bytes, including UTF-8 sequences, pass through.
inline std::string escape_string(std::string_view s) {
    std::string out;
    out.reserve(s.size() + 2);
    out += '"';
    for (unsigned char c : s) {
        switch (c) {
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\b': out += "\\b"; break;
            case '\f': out += "\\f"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (c < 0x20) {
                    char buf[8];
                    std::snprintf(buf, sizeof buf, "\\u%04x", c);
                    out += buf;
                } else {
                    out += static_cast<char>(c);
                }
        }
    }
    out += '"';
    return out;
}

// Source text for a single token: strings are re-escaped, everything else is
// emitted exactly as written (numbers keep their original spelling).
inline std::string token_text(const Token& t) {
    return t.type == TokenType::String ? escape_string(t.value) : t.value;
}

// Returns src with all insignificant whitespace removed. The input is
// validated first, so invalid JSON throws TokenizeError / SyntaxError.
inline std::string minify(std::string_view src) {
    validate(src);
    std::string out;
    out.reserve(src.size());
    Tokenizer lexer(src);
    for (Token tok = lexer.next(); tok.type != TokenType::End; tok = lexer.next())
        out += token_text(tok);
    return out;
}

// Re-formats a valid document with one element or member per line, each
// nesting level indented by `indent` spaces and a space after every ':'.
// Empty containers stay on one line as {} or []. No trailing newline is
// added. Invalid JSON throws TokenizeError / SyntaxError.
inline std::string pretty(std::string_view src, unsigned indent = 2) {
    validate(src);
    std::vector<Token> toks = tokenize(src);
    std::string out;
    out.reserve(src.size() * 2);
    std::size_t depth = 0;
    auto newline = [&] {
        out += '\n';
        out.append(depth * indent, ' ');
    };
    for (std::size_t i = 0; i + 1 < toks.size(); ++i) {  // skip the End token
        const Token& t = toks[i];
        switch (t.type) {
            case TokenType::LBrace:
            case TokenType::LBracket: {
                TokenType close = t.type == TokenType::LBrace ? TokenType::RBrace : TokenType::RBracket;
                out += t.value;
                if (toks[i + 1].type == close) {  // empty container
                    out += toks[++i].value;
                } else {
                    ++depth;
                    newline();
                }
                break;
            }
            case TokenType::RBrace:
            case TokenType::RBracket:
                --depth;
                newline();
                out += t.value;
                break;
            case TokenType::Comma:
                out += ',';
                newline();
                break;
            case TokenType::Colon:
                out += ": ";
                break;
            default:
                out += token_text(t);
        }
    }
    return out;
}

}  // namespace jt
