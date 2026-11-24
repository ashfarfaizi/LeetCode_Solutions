#pragma once

#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
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
};

class TokenizeError : public std::runtime_error {
public:
    TokenizeError(const std::string& msg, std::size_t offset)
        : std::runtime_error(msg + " at offset " + std::to_string(offset)), offset_(offset) {}
    std::size_t offset() const { return offset_; }

private:
    std::size_t offset_;
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
        if (pos_ >= src_.size()) return {TokenType::End, "", start};
        char c = src_[pos_];
        switch (c) {
            case '{': ++pos_; return {TokenType::LBrace, "{", start};
            case '}': ++pos_; return {TokenType::RBrace, "}", start};
            case '[': ++pos_; return {TokenType::LBracket, "[", start};
            case ']': ++pos_; return {TokenType::RBracket, "]", start};
            case ':': ++pos_; return {TokenType::Colon, ":", start};
            case ',': ++pos_; return {TokenType::Comma, ",", start};
            case '"': return {TokenType::String, read_string(), start};
            case 't': expect_word("true"); return {TokenType::True, "true", start};
            case 'f': expect_word("false"); return {TokenType::False, "false", start};
            case 'n': expect_word("null"); return {TokenType::Null, "null", start};
            default: break;
        }
        if (c == '-' || is_digit(c)) return {TokenType::Number, read_number(), start};
        throw TokenizeError(std::string("unexpected character '") + c + "'", start);
    }

    std::size_t position() const { return pos_; }

private:
    std::string_view src_;
    std::size_t pos_ = 0;

    static bool is_digit(char c) { return c >= '0' && c <= '9'; }

    void skip_whitespace() {
        while (pos_ < src_.size() &&
               (src_[pos_] == ' ' || src_[pos_] == '\t' || src_[pos_] == '\n' || src_[pos_] == '\r'))
            ++pos_;
    }

    void expect_word(std::string_view word) {
        if (src_.substr(pos_, word.size()) != word)
            throw TokenizeError("invalid literal, expected '" + std::string(word) + "'", pos_);
        pos_ += word.size();
        if (pos_ < src_.size() && std::isalnum(static_cast<unsigned char>(src_[pos_])))
            throw TokenizeError("invalid literal", pos_);
    }

    std::string read_string() {
        std::size_t start = pos_++;  // opening quote
        std::string out;
        while (true) {
            if (pos_ >= src_.size()) throw TokenizeError("unterminated string", start);
            char c = src_[pos_++];
            if (c == '"') return out;
            if (static_cast<unsigned char>(c) < 0x20)
                throw TokenizeError("control character in string", pos_ - 1);
            if (c != '\\') {
                out += c;
                continue;
            }
            if (pos_ >= src_.size()) throw TokenizeError("unterminated string", start);
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
                default: throw TokenizeError(std::string("invalid escape '\\") + e + "'", pos_ - 2);
            }
        }
    }

    // number = [ "-" ] int [ frac ] [ exp ], int has no leading zeros.
    std::string read_number() {
        std::size_t start = pos_;
        if (src_[pos_] == '-') ++pos_;
        if (pos_ >= src_.size() || !is_digit(src_[pos_]))
            throw TokenizeError("expected digit", pos_);
        if (src_[pos_] == '0') {
            ++pos_;
            if (pos_ < src_.size() && is_digit(src_[pos_]))
                throw TokenizeError("leading zeros are not allowed", pos_);
        } else {
            while (pos_ < src_.size() && is_digit(src_[pos_])) ++pos_;
        }
        if (pos_ < src_.size() && src_[pos_] == '.') {
            ++pos_;
            if (pos_ >= src_.size() || !is_digit(src_[pos_]))
                throw TokenizeError("expected digit after '.'", pos_);
            while (pos_ < src_.size() && is_digit(src_[pos_])) ++pos_;
        }
        if (pos_ < src_.size() && (src_[pos_] == 'e' || src_[pos_] == 'E')) {
            ++pos_;
            if (pos_ < src_.size() && (src_[pos_] == '+' || src_[pos_] == '-')) ++pos_;
            if (pos_ >= src_.size() || !is_digit(src_[pos_]))
                throw TokenizeError("expected digit in exponent", pos_);
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
