#pragma once

#include <cstddef>
#include <string>
#include <string_view>

#include "json_tokenizer.hpp"

namespace jt {

// Returns a copy of src in which every // line comment and /* block */
// comment (as used by JSONC config files) is overwritten with spaces.
// Newlines inside comments are kept, so the result has the same length and
// every byte keeps its line and column: errors reported on the stripped text
// point at the right place in the original. Comment markers inside string
// literals are left alone. An unterminated block comment throws
// TokenizeError at the position of its opening "/*".
inline std::string strip_comments(std::string_view src) {
    std::string out(src);
    std::size_t line = 1, line_start = 0;
    bool in_string = false;
    for (std::size_t i = 0; i < out.size(); ++i) {
        char c = out[i];
        if (c == '\n') {
            ++line;
            line_start = i + 1;
            continue;
        }
        if (in_string) {
            if (c == '\\') ++i;  // skip the escaped character (never a newline in valid JSON)
            else if (c == '"') in_string = false;
            continue;
        }
        if (c == '"') {
            in_string = true;
            continue;
        }
        if (c != '/' || i + 1 >= out.size()) continue;
        if (out[i + 1] == '/') {
            while (i < out.size() && out[i] != '\n') out[i++] = ' ';
            --i;  // let the loop see the newline
        } else if (out[i + 1] == '*') {
            std::size_t open = i, open_line = line, open_col = i - line_start + 1;
            out[i] = out[i + 1] = ' ';
            i += 2;
            while (i + 1 < out.size() && !(out[i] == '*' && out[i + 1] == '/')) {
                if (out[i] == '\n') {
                    ++line;
                    line_start = i + 1;
                } else {
                    out[i] = ' ';
                }
                ++i;
            }
            if (i + 1 >= out.size())
                throw TokenizeError("unterminated block comment", open, open_line, open_col);
            out[i] = out[i + 1] = ' ';
            ++i;
        }
    }
    return out;
}

}  // namespace jt
