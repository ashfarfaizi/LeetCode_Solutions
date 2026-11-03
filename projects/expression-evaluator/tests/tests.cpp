// Minimal self-contained test runner: no external framework needed.
#include <cmath>
#include <iostream>
#include <string>

#include "lexer.hpp"

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

int main() {
    testLexer();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
