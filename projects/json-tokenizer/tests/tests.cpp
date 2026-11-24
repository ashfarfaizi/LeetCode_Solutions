#include "json_tokenizer.hpp"

#include <cstdio>
#include <functional>
#include <string>
#include <vector>

static int failures = 0;
static int passed = 0;

#define CHECK(cond)                                                     \
    do {                                                                \
        if (cond) {                                                     \
            ++passed;                                                   \
        } else {                                                        \
            ++failures;                                                 \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        }                                                               \
    } while (0)

static bool fails(const std::string& src) {
    try {
        jt::tokenize(src);
    } catch (const jt::TokenizeError&) {
        return true;
    }
    return false;
}

static std::vector<jt::TokenType> types(const std::string& src) {
    std::vector<jt::TokenType> out;
    for (const auto& t : jt::tokenize(src)) out.push_back(t.type);
    return out;
}

static void test_punctuation_and_literals() {
    using T = jt::TokenType;
    CHECK((types("{ } [ ] : ,") ==
           std::vector<T>{T::LBrace, T::RBrace, T::LBracket, T::RBracket, T::Colon, T::Comma, T::End}));
    CHECK((types("[true,false,null]") ==
           std::vector<T>{T::LBracket, T::True, T::Comma, T::False, T::Comma, T::Null, T::RBracket, T::End}));
    CHECK((types(" \t\r\n") == std::vector<T>{T::End}));
    auto toks = jt::tokenize("  {\"a\": 1}");
    CHECK(toks[0].offset == 2);
    CHECK(toks[1].offset == 3);
    CHECK(toks[3].offset == 8);
    CHECK(fails("tru"));
    CHECK(fails("nulls"));
    CHECK(fails("@"));
}

static void test_strings() {
    auto toks = jt::tokenize(R"("hello" "a\"b\\c\/d" "\n\t\r\b\f" "")");
    CHECK(toks[0].value == "hello");
    CHECK(toks[1].value == "a\"b\\c/d");
    CHECK(toks[2].value == "\n\t\r\b\f");
    CHECK(toks[3].value.empty());
    CHECK(fails("\"abc"));
    CHECK(fails("\"bad \\q escape\""));
    CHECK(fails("\"tab\there\""));
    CHECK(fails("\"ends with backslash\\"));
}

static void test_unicode_escapes() {
    auto toks = jt::tokenize(R"("\u0041" "\u00e9" "\u20AC" "\ud83d\ude00" "a\u0000b")");
    CHECK(toks[0].value == "A");
    CHECK(toks[1].value == "\xC3\xA9");          // é
    CHECK(toks[2].value == "\xE2\x82\xAC");      // €
    CHECK(toks[3].value == "\xF0\x9F\x98\x80");  // U+1F600
    CHECK(toks[4].value == std::string("a\0b", 3));
    CHECK(fails(R"("\u12")"));
    CHECK(fails(R"("\u12G4")"));
    CHECK(fails(R"("\ud83d")"));         // high surrogate alone
    CHECK(fails(R"("\ud83d\u0041")"));   // high + non-low
    CHECK(fails(R"("\ude00")"));         // low surrogate alone
}

static void test_numbers() {
    for (const char* ok : {"0", "-0", "12", "-12", "3.25", "1e10", "1E+2", "-2.5e-3", "0.0"}) {
        auto toks = jt::tokenize(ok);
        CHECK(toks[0].type == jt::TokenType::Number && toks[0].value == ok);
    }
    auto toks = jt::tokenize("[1,-2]");
    CHECK(toks[1].value == "1" && toks[3].value == "-2");
    CHECK(fails("01"));
    CHECK(fails("-"));
    CHECK(fails("1."));
    CHECK(fails(".5"));
    CHECK(fails("1e"));
    CHECK(fails("+1"));
}

static void test_error_offsets() {
    try {
        jt::tokenize("[1, @]");
        CHECK(false);
    } catch (const jt::TokenizeError& e) {
        CHECK(e.offset() == 4);
        CHECK(e.line() == 1 && e.column() == 5);
    }
}

static void test_line_and_column() {
    auto toks = jt::tokenize("{\n  \"a\": [1,\r\n    2]\n}");
    CHECK(toks[0].line == 1 && toks[0].column == 1);  // {
    CHECK(toks[1].line == 2 && toks[1].column == 3);  // "a"
    CHECK(toks[3].line == 2 && toks[3].column == 8);  // [
    CHECK(toks[6].line == 3 && toks[6].column == 5);  // 2
    CHECK(toks[8].line == 4 && toks[8].column == 1);  // }
    CHECK(toks[9].type == jt::TokenType::End && toks[9].line == 4 && toks[9].column == 2);
    try {
        jt::tokenize("[\n  true,\n  nul ]");
        CHECK(false);
    } catch (const jt::TokenizeError& e) {
        CHECK(e.line() == 3 && e.column() == 3);
        CHECK(std::string(e.what()).find("line 3, column 3") != std::string::npos);
    }
}

int main() {
    test_punctuation_and_literals();
    test_strings();
    test_unicode_escapes();
    test_numbers();
    test_error_offsets();
    test_line_and_column();
    std::printf("%d passed, %d failed\n", passed, failures);
    return failures == 0 ? 0 : 1;
}
