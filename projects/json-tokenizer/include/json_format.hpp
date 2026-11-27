#pragma once

#include <cstdio>
#include <string>
#include <string_view>

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

}  // namespace jt
