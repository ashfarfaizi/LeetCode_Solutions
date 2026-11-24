#pragma once

#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace jt {

enum class TokenType {
    LBrace,    // {
    RBrace,    // }
    LBracket,  // [
    RBracket,  // ]
    Colon,     // :
    Comma,     // ,
    String,    // value holds the decoded text
    Number,    // value holds the literal as written
    True,
    False,
    Null,
    End,
};

struct Token {
    TokenType type;
    std::string value;
    std::size_t offset;  // byte offset of the token's first character
    std::size_t line;    // 1-based line of the first character
    std::size_t column;  // 1-based byte column of the first character
};

class TokenizeError : public std::runtime_error {
public:
    TokenizeError(const std::string& msg, std::size_t offset, std::size_t line, std::size_t column)
        : std::runtime_error(msg + " at line " + std::to_string(line) + ", column " +
                             std::to_string(column)),
          offset_(offset), line_(line), column_(column) {}
    std::size_t offset() const { return offset_; }
    std::size_t line() const { return line_; }
    std::size_t column() const { return column_; }

private:
    std::size_t offset_, line_, column_;
};

inline const char* type_name(TokenType t) {
    switch (t) {
        case TokenType::LBrace: return "LBrace";
        case TokenType::RBrace: return "RBrace";
        case TokenType::LBracket: return "LBracket";
        case TokenType::RBracket: return "RBracket";
        case TokenType::Colon: return "Colon";
        case TokenType::Comma: return "Comma";
        case TokenType::String: return "String";
        case TokenType::Number: return "Number";
        case TokenType::True: return "True";
        case TokenType::False: return "False";
        case TokenType::Null: return "Null";
        case TokenType::End: return "End";
    }
    return "?";
}

// Streaming tokenizer for RFC 8259 JSON text. Call next() until it returns
// a token of type End. Throws TokenizeError on malformed input.
class Tokenizer {
public:
    explicit Tokenizer(std::string_view src) : src_(src) {}

    Token next() {
        skip_whitespace();
        std::size_t start = pos_;
        if (pos_ >= src_.size()) return make(TokenType::End, "", start);
        char c = src_[pos_];
        switch (c) {
            case '{': ++pos_; return make(TokenType::LBrace, "{", start);
            case '}': ++pos_; return make(TokenType::RBrace, "}", start);
            case '[': ++pos_; return make(TokenType::LBracket, "[", start);
            case ']': ++pos_; return make(TokenType::RBracket, "]", start);
            case ':': ++pos_; return make(TokenType::Colon, ":", start);
            case ',': ++pos_; return make(TokenType::Comma, ",", start);
            case '"': return make(TokenType::String, read_string(), start);
            case 't': expect_word("true"); return make(TokenType::True, "true", start);
            case 'f': expect_word("false"); return make(TokenType::False, "false", start);
            case 'n': expect_word("null"); return make(TokenType::Null, "null", start);
            default: break;
        }
        if (c == '-' || is_digit(c)) return make(TokenType::Number, read_number(), start);
        fail(std::string("unexpected character '") + c + "'", start);
    }

    std::size_t position() const { return pos_; }

private:
    std::string_view src_;
    std::size_t pos_ = 0;
    std::size_t line_ = 1;
    std::size_t line_start_ = 0;  // offset of the first byte of the current line

    // Raw newlines can only occur in whitespace (strings reject them), so a
    // token never spans lines and its column is relative to line_start_.
    Token make(TokenType type, std::string value, std::size_t offset) const {
        return {type, std::move(value), offset, line_, offset - line_start_ + 1};
    }

    [[noreturn]] void fail(const std::string& msg, std::size_t offset) const {
        throw TokenizeError(msg, offset, line_, offset - line_start_ + 1);
    }

    static bool is_digit(char c) { return c >= '0' && c <= '9'; }

    void skip_whitespace() {
        while (pos_ < src_.size()) {
            char c = src_[pos_];
            if (c == '\n') {
                ++line_;
                line_start_ = pos_ + 1;
            } else if (c != ' ' && c != '\t' && c != '\r') {
                break;
            }
            ++pos_;
        }
    }

    void expect_word(std::string_view word) {
        if (src_.substr(pos_, word.size()) != word)
            fail("invalid literal, expected '" + std::string(word) + "'", pos_);
        pos_ += word.size();
        if (pos_ < src_.size() && std::isalnum(static_cast<unsigned char>(src_[pos_])))
            fail("invalid literal", pos_);
    }

    std::string read_string() {
        std::size_t start = pos_++;  // opening quote
        std::string out;
        while (true) {
            if (pos_ >= src_.size()) fail("unterminated string", start);
            char c = src_[pos_++];
            if (c == '"') return out;
            if (static_cast<unsigned char>(c) < 0x20)
                fail("control character in string", pos_ - 1);
            if (c != '\\') {
                out += c;
                continue;
            }
            if (pos_ >= src_.size()) fail("unterminated string", start);
            char e = src_[pos_++];
            switch (e) {
                case '"': out += '"'; break;
                case '\\': out += '\\'; break;
                case '/': out += '/'; break;
                case 'b': out += '\b'; break;
                case 'f': out += '\f'; break;
                case 'n': out += '\n'; break;
                case 'r': out += '\r'; break;
                case 't': out += '\t'; break;
                case 'u': read_unicode_escape(out, pos_ - 2); break;
                default: fail(std::string("invalid escape '\\") + e + "'", pos_ - 2);
            }
        }
    }

    unsigned read_hex4() {
        if (src_.size() - pos_ < 4) fail("truncated \\u escape", pos_);
        unsigned v = 0;
        for (int i = 0; i < 4; ++i) {
            char h = src_[pos_++];
            v <<= 4;
            if (h >= '0' && h <= '9') v |= static_cast<unsigned>(h - '0');
            else if (h >= 'a' && h <= 'f') v |= static_cast<unsigned>(h - 'a' + 10);
            else if (h >= 'A' && h <= 'F') v |= static_cast<unsigned>(h - 'A' + 10);
            else fail("invalid hex digit in \\u escape", pos_ - 1);
        }
        return v;
    }

    // Decodes \uXXXX (pos_ is just past the 'u'), combining UTF-16
    // surrogate pairs, and appends the code point as UTF-8.
    void read_unicode_escape(std::string& out, std::size_t escape_start) {
        unsigned cp = read_hex4();
        if (cp >= 0xDC00 && cp <= 0xDFFF)
            fail("unpaired low surrogate", escape_start);
        if (cp >= 0xD800 && cp <= 0xDBFF) {
            if (src_.substr(pos_, 2) != "\\u")
                fail("unpaired high surrogate", escape_start);
            pos_ += 2;
            unsigned lo = read_hex4();
            if (lo < 0xDC00 || lo > 0xDFFF)
                fail("invalid low surrogate", pos_ - 6);
            cp = 0x10000 + ((cp - 0xD800) << 10) + (lo - 0xDC00);
        }
        append_utf8(out, cp);
    }

    static void append_utf8(std::string& out, unsigned cp) {
        if (cp < 0x80) {
            out += static_cast<char>(cp);
        } else if (cp < 0x800) {
            out += static_cast<char>(0xC0 | (cp >> 6));
            out += static_cast<char>(0x80 | (cp & 0x3F));
        } else if (cp < 0x10000) {
            out += static_cast<char>(0xE0 | (cp >> 12));
            out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
            out += static_cast<char>(0x80 | (cp & 0x3F));
        } else {
            out += static_cast<char>(0xF0 | (cp >> 18));
            out += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
            out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
            out += static_cast<char>(0x80 | (cp & 0x3F));
        }
    }

    // number = [ "-" ] int [ frac ] [ exp ], int has no leading zeros.
    std::string read_number() {
        std::size_t start = pos_;
        if (src_[pos_] == '-') ++pos_;
        if (pos_ >= src_.size() || !is_digit(src_[pos_]))
            fail("expected digit", pos_);
        if (src_[pos_] == '0') {
            ++pos_;
            if (pos_ < src_.size() && is_digit(src_[pos_]))
                fail("leading zeros are not allowed", pos_);
        } else {
            while (pos_ < src_.size() && is_digit(src_[pos_])) ++pos_;
        }
        if (pos_ < src_.size() && src_[pos_] == '.') {
            ++pos_;
            if (pos_ >= src_.size() || !is_digit(src_[pos_]))
                fail("expected digit after '.'", pos_);
            while (pos_ < src_.size() && is_digit(src_[pos_])) ++pos_;
        }
        if (pos_ < src_.size() && (src_[pos_] == 'e' || src_[pos_] == 'E')) {
            ++pos_;
            if (pos_ < src_.size() && (src_[pos_] == '+' || src_[pos_] == '-')) ++pos_;
            if (pos_ >= src_.size() || !is_digit(src_[pos_]))
                fail("expected digit in exponent", pos_);
            while (pos_ < src_.size() && is_digit(src_[pos_])) ++pos_;
        }
        return std::string(src_.substr(start, pos_ - start));
    }
};

// Convenience: tokenizes the whole input, including the trailing End token.
inline std::vector<Token> tokenize(std::string_view src) {
    Tokenizer t(src);
    std::vector<Token> out;
    do {
        out.push_back(t.next());
    } while (out.back().type != TokenType::End);
    return out;
}

}  // namespace jt
