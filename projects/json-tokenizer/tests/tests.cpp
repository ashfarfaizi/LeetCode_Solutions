#include "json_comments.hpp"
#include "json_format.hpp"
#include "json_stats.hpp"
#include "json_tokenizer.hpp"
#include "json_validate.hpp"

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

static void test_validate() {
    for (const char* ok : {"1", "\"s\"", "null", " [ ] ", "{}", "[1, [2, [3]], {\"a\": {}}]",
                           "{\"k\": [true, false, null], \"n\": -1.5e3}"}) {
        std::string err;
        bool valid = jt::is_valid(ok, &err);
        CHECK(valid);
        if (!valid) std::printf("  %s -> %s\n", ok, err.c_str());
    }
    for (const char* bad : {"", "[", "]", "[1,]", "[,1]", "{\"a\"}", "{\"a\":}", "{1: 2}",
                            "{\"a\": 1,}", "[1 2]", "1 2", "[}", "{]", ":", "{\"a\" 1}"}) {
        CHECK(!jt::is_valid(bad));
    }
    try {
        jt::validate("{\n  \"a\": [1, 2,]\n}");
        CHECK(false);
    } catch (const jt::SyntaxError& e) {
        CHECK(e.line() == 2 && e.column() == 14);
        CHECK(std::string(e.what()).find("expected a value but found ']'") == 0);
    }
    // lexical errors still surface through validate
    std::string err;
    CHECK(!jt::is_valid("[01]", &err));
    CHECK(err.find("leading zeros") != std::string::npos);

    // deep nesting does not recurse, and max_depth is enforced
    std::string deep = std::string(100000, '[') + std::string(100000, ']');
    CHECK(jt::is_valid(deep));
    bool threw = false;
    try {
        jt::validate("[[[1]]]", 2);
    } catch (const jt::SyntaxError&) {
        threw = true;
    }
    CHECK(threw);
    jt::validate("[[1]]", 2);  // exactly at the limit is fine
}

static bool throws_on(std::string (*fn)(std::string_view), const std::string& src) {
    try {
        fn(src);
    } catch (const jt::TokenizeError&) {
        return true;
    }
    return false;
}

static void test_escape_and_minify() {
    CHECK(jt::escape_string("plain") == "\"plain\"");
    CHECK(jt::escape_string("a\"b\\c") == "\"a\\\"b\\\\c\"");
    CHECK(jt::escape_string("\n\t\r\b\f") == "\"\\n\\t\\r\\b\\f\"");
    CHECK(jt::escape_string(std::string("x\0\x1f", 3)) == "\"x\\u0000\\u001f\"");
    CHECK(jt::escape_string("\xC3\xA9") == "\"\xC3\xA9\"");  // UTF-8 kept as is
    CHECK(jt::escape_string("a/b") == "\"a/b\"");

    CHECK(jt::minify(" { \"a\" : [ 1 , 2.50 ,\n true ] ,\t\"b\" : null } ") ==
          "{\"a\":[1,2.50,true],\"b\":null}");
    CHECK(jt::minify("\"\\u0041\\/\"") == "\"A/\"");  // escapes normalised
    CHECK(jt::minify("[ ]") == "[]");
    CHECK(jt::minify("-1e+5") == "-1e+5");
    std::string doc = R"({"k": ["x\ny", {"z": false}], "e": {}})";
    CHECK(jt::minify(jt::minify(doc)) == jt::minify(doc));  // idempotent
    CHECK(jt::is_valid(jt::minify(doc)));
    CHECK(throws_on(jt::minify, "[1,]"));
    CHECK(throws_on(jt::minify, "{\"a\": tru}"));
}

static std::string pretty4(std::string_view src) { return jt::pretty(src, 4); }

static void test_pretty() {
    CHECK(jt::pretty("1") == "1");
    CHECK(jt::pretty(" [ ] ") == "[]");
    CHECK(jt::pretty("{ }") == "{}");
    CHECK(jt::pretty("[1,2]") == "[\n  1,\n  2\n]");
    CHECK(jt::pretty(R"({"a":[1,{}],"b":{"c":"x\ty"}})") ==
          "{\n"
          "  \"a\": [\n"
          "    1,\n"
          "    {}\n"
          "  ],\n"
          "  \"b\": {\n"
          "    \"c\": \"x\\ty\"\n"
          "  }\n"
          "}");
    CHECK(pretty4("[[true]]") == "[\n    [\n        true\n    ]\n]");
    CHECK(jt::pretty("[null,[]]", 0) == "[\nnull,\n[]\n]");
    // pretty output round-trips through minify
    std::string doc = R"({"k":[1.50,"\u00e9",[[]],{"z":false}],"e":{}})";
    CHECK(jt::minify(jt::pretty(doc)) == jt::minify(doc));
    CHECK(throws_on(pretty4, "[1 2]"));
}

static void test_stats() {
    jt::Stats s = jt::stats(R"({"a": [1, 2.5, "x"], "b": {"c": null, "d": [true, false, []]}, "e": "y"})");
    CHECK(s.objects == 2);
    CHECK(s.arrays == 3);
    CHECK(s.keys == 5);
    CHECK(s.strings == 2);
    CHECK(s.numbers == 2);
    CHECK(s.booleans == 2);
    CHECK(s.nulls == 1);
    CHECK(s.max_depth == 4);

    jt::Stats scalar = jt::stats("\"just a string\"");
    CHECK(scalar.strings == 1 && scalar.keys == 0 && scalar.max_depth == 0);
    CHECK(jt::stats("[[[]]]").max_depth == 3);
    CHECK(jt::stats("[\"k\", \"v\"]").keys == 0);  // strings in arrays are values
    bool threw = false;
    try {
        jt::stats("{\"a\" 1}");
    } catch (const jt::SyntaxError&) {
        threw = true;
    }
    CHECK(threw);
}

static void test_strip_comments() {
    std::string src = "{\n  // name\n  \"a\": 1, /* inline */ \"b\": [2 /* x\n y */, 3]\n}";
    std::string out = jt::strip_comments(src);
    CHECK(out.size() == src.size());
    CHECK(jt::minify(out) == "{\"a\":1,\"b\":[2,3]}");
    auto toks = jt::tokenize(out);
    CHECK(toks[1].line == 3 && toks[1].column == 3);  // "a" keeps its position
    CHECK(toks[10].type == jt::TokenType::Number && toks[10].line == 4);  // 3 after the multi-line comment

    // markers inside strings are not comments, including after an escaped quote
    CHECK(jt::strip_comments(R"(["http://x", "/*no*/", "q\"//"])") == R"(["http://x", "/*no*/", "q\"//"])");
    CHECK(jt::strip_comments("1 // trailing") == "1            ");
    CHECK(jt::strip_comments("[1, 2 / 3]") == "[1, 2 / 3]");  // lone slash stays and fails later
    CHECK(!jt::is_valid(jt::strip_comments("[1, 2 / 3]")));
    try {
        jt::strip_comments("[1,\n  /* open");
        CHECK(false);
    } catch (const jt::TokenizeError& e) {
        CHECK(e.offset() == 6 && e.line() == 2 && e.column() == 3);
    }
}

int main() {
    test_punctuation_and_literals();
    test_strings();
    test_unicode_escapes();
    test_numbers();
    test_error_offsets();
    test_line_and_column();
    test_validate();
    test_escape_and_minify();
    test_pretty();
    test_stats();
    test_strip_comments();
    std::printf("%d passed, %d failed\n", passed, failures);
    return failures == 0 ? 0 : 1;
}
