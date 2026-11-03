// Minimal self-contained test runner: no external framework needed.
#include <cmath>
#include <iostream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"

using namespace expr;

static int failures = 0, checks = 0;

#define CHECK(cond)                                                          \
    do {                                                                     \
        ++checks;                                                            \
        if (!(cond)) {                                                       \
            ++failures;                                                      \
            std::cerr << __FILE__ << ":" << __LINE__ << ": FAILED " #cond "\n"; \
        }                                                                    \
    } while (0)

template <typename F>
static bool throwsParseError(F f) {
    try {
        f();
    } catch (const ParseError&) {
        return true;
    }
    return false;
}

static void testLexer() {
    auto t = tokenize("3 + 4.5*(2-1)");
    CHECK(t.size() == 9);
    CHECK(t[0] == (Token{TokenType::Number, 3.0, '\0'}));
    CHECK(t[1] == (Token{TokenType::Operator, 0.0, '+'}));
    CHECK(t[2] == (Token{TokenType::Number, 4.5, '\0'}));
    CHECK(t[4].type == TokenType::LParen);
    CHECK(t[8].type == TokenType::RParen);

    CHECK(tokenize("").empty());
    CHECK(tokenize("   \t ").empty());
    CHECK(tokenize(".25")[0].value == 0.25);
    CHECK(tokenize("2^3")[1].op == '^');

    CHECK(throwsParseError([] { tokenize("1 $ 2"); }));
    CHECK(throwsParseError([] { tokenize("1.2.3"); }));
    CHECK(throwsParseError([] { tokenize("."); }));
}

// Render RPN tokens as a compact string, e.g. "3 4 2 * +".
static std::string rpnString(const std::string& src) {
    std::string out;
    for (const Token& t : toRPN(tokenize(src))) {
        if (!out.empty()) out += ' ';
        if (t.type == TokenType::Number) {
            double v = t.value;
            out += (v == std::floor(v)) ? std::to_string(static_cast<long long>(v)) : std::to_string(v);
        } else {
            out += t.op;
        }
    }
    return out;
}

static void testParser() {
    CHECK(rpnString("3 + 4 * 2") == "3 4 2 * +");
    CHECK(rpnString("(3 + 4) * 2") == "3 4 + 2 *");
    CHECK(rpnString("10 - 4 - 3") == "10 4 - 3 -");      // left-assoc
    CHECK(rpnString("2 ^ 3 ^ 2") == "2 3 2 ^ ^");        // right-assoc
    CHECK(rpnString("8 / 2 * 3") == "8 2 / 3 *");
    CHECK(rpnString("((1))") == "1");
    CHECK(rpnString("") == "");

    CHECK(throwsParseError([] { toRPN(tokenize("(1 + 2")); }));
    CHECK(throwsParseError([] { toRPN(tokenize("1 + 2)")); }));
}

int main() {
    testLexer();
    testParser();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
