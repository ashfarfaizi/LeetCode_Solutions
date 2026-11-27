#pragma once

#include <cstddef>
#include <string_view>
#include <vector>

#include "json_tokenizer.hpp"
#include "json_validate.hpp"

namespace jt {

// Shape summary of a JSON document.
struct Stats {
    std::size_t objects = 0;
    std::size_t arrays = 0;
    std::size_t keys = 0;      // object member names
    std::size_t strings = 0;   // string values (keys are not counted here)
    std::size_t numbers = 0;
    std::size_t booleans = 0;
    std::size_t nulls = 0;
    std::size_t max_depth = 0;  // 0 for a scalar document, 1 for [1], ...
};

// Validates src and counts its values. A string token is a key when the next
// token is ':' (the only place a colon can appear in valid JSON).
inline Stats stats(std::string_view src) {
    validate(src);
    std::vector<Token> toks = tokenize(src);
    Stats s;
    std::size_t depth = 0;
    for (std::size_t i = 0; i < toks.size(); ++i) {
        switch (toks[i].type) {
            case TokenType::LBrace:
            case TokenType::LBracket:
                ++(toks[i].type == TokenType::LBrace ? s.objects : s.arrays);
                if (++depth > s.max_depth) s.max_depth = depth;
                break;
            case TokenType::RBrace:
            case TokenType::RBracket:
                --depth;
                break;
            case TokenType::String:
                ++(toks[i + 1].type == TokenType::Colon ? s.keys : s.strings);
                break;
            case TokenType::Number: ++s.numbers; break;
            case TokenType::True:
            case TokenType::False: ++s.booleans; break;
            case TokenType::Null: ++s.nulls; break;
            default: break;
        }
    }
    return s;
}

}  // namespace jt
