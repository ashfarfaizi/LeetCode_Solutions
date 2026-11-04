// Minimal self-contained test runner: no external framework needed.
#include <cmath>
#include <iostream>
#include <string>

#include "evaluator.hpp"
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
    CHECK(tokenize("7%3")[1].op == '%');

    auto id = tokenize("2*pi_2 + x1");
    CHECK(id.size() == 5);
    CHECK(id[2] == (Token{TokenType::Identifier, 0.0, '\0', "pi_2"}));
    CHECK(id[4].name == "x1");

    CHECK(throwsParseError([] { tokenize("1 $ 2"); }));
    CHECK(throwsParseError([] { tokenize("1.2.3"); }));
    CHECK(throwsParseError([] { tokenize("."); }));
}

// Render RPN tokens as a compact string, e.g. "3 4 2 * +".
static std::string rpnString(const std::string& src) {
    std::string out;
    for (const Token& t : toRPN(tokenize(src))) {
        if (!out.empty()) out += ' ';
        if (t.type == TokenType::Identifier || t.type == TokenType::Function) {
            out += t.name;
        } else if (t.type == TokenType::Number) {
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
    CHECK(rpnString("1 + 7 % 4") == "1 7 4 % +");
    CHECK(rpnString("((1))") == "1");
    CHECK(rpnString("") == "");

    CHECK(rpnString("-3 + 4") == "3 u 4 +");
    CHECK(rpnString("-2 ^ 2") == "2 2 ^ u");
    CHECK(rpnString("2 ^ -1") == "2 1 u ^");
    CHECK(rpnString("+5") == "5");
    CHECK(rpnString("2 * pi") == "2 pi *");
    CHECK(rpnString("sqrt(x + 1)") == "x 1 + sqrt");
    CHECK(rpnString("-abs(2) ^ 2") == "2 abs 2 ^ u");
    CHECK(rpnString("sin(cos(0))") == "0 cos sin");
    CHECK(rpnString("max(1, 2 + 3)") == "1 2 3 + max");
    CHECK(rpnString("min(a, max(b, c), d)") == "a b c max d min");
    CHECK(toRPN(tokenize("max(1, 2, 3)")).back().value == 3);
    CHECK(throwsParseError([] { toRPN(tokenize("sqrt(4")); }));
    CHECK(throwsParseError([] { toRPN(tokenize("1, 2")); }));
    CHECK(throwsParseError([] { toRPN(tokenize("(1, 2)")); }));

    CHECK(throwsParseError([] { toRPN(tokenize("(1 + 2")); }));
    CHECK(throwsParseError([] { toRPN(tokenize("* 3")); }));
    CHECK(throwsParseError([] { toRPN(tokenize("2 * / 3")); }));
    CHECK(throwsParseError([] { toRPN(tokenize("1 + 2)")); }));
}

static bool near(double a, double b) { return std::fabs(a - b) < 1e-9; }

template <typename F>
static bool throwsEvalError(F f) {
    try {
        f();
    } catch (const EvalError&) {
        return true;
    }
    return false;
}

static void testEvaluator() {
    CHECK(near(evaluate("3 + 4 * 2"), 11));
    CHECK(near(evaluate("(3 + 4) * 2"), 14));
    CHECK(near(evaluate("10 - 4 - 3"), 3));
    CHECK(near(evaluate("2 ^ 3 ^ 2"), 512));
    CHECK(near(evaluate("7 / 2"), 3.5));
    CHECK(near(evaluate("1.5 * (2 + 0.5)"), 3.75));
    CHECK(near(evaluate("42"), 42));
    CHECK(near(evaluate("(3 + 4) * 2 ^ 2"), 28));  // README example

    CHECK(near(evaluate("-3 + 4"), 1));
    CHECK(near(evaluate("-2 ^ 2"), -4));
    CHECK(near(evaluate("2 ^ -1"), 0.5));
    CHECK(near(evaluate("--5"), 5));
    CHECK(near(evaluate("3 * -(2 + 1)"), -9));
    CHECK(near(evaluate("-3 * 2"), -6));

    CHECK(near(evaluate("7 % 3"), 1));
    CHECK(near(evaluate("-7 % 3"), -1));
    CHECK(near(evaluate("5.5 % 2"), 1.5));
    CHECK(near(evaluate("2 * 7 % 4"), 2));  // left-assoc with *

    CHECK(near(evaluate("pi"), 3.14159265358979323846));
    CHECK(near(evaluate("2 * pi"), 6.28318530717958647692));
    CHECK(near(evaluate("e ^ 2"), 7.38905609893064951));

    CHECK(throwsEvalError([] { evaluate("1 / 0"); }));
    CHECK(near(evaluate("sqrt(16) + 1"), 5));
    CHECK(near(evaluate("abs(-3.5)"), 3.5));
    CHECK(near(evaluate("ln(e ^ 3)"), 3));
    CHECK(near(evaluate("log10(1000)"), 3));
    CHECK(near(evaluate("sin(pi / 2) + cos(0)"), 2));
    CHECK(near(evaluate("floor(2.7) + ceil(2.1) + round(2.5)"), 8));
    CHECK(near(evaluate("2 * sqrt(sqrt(16))"), 4));

    CHECK(throwsEvalError([] { evaluate("foo + 1"); }));
    CHECK(throwsEvalError([] { evaluate("foo(1)"); }));
    CHECK(throwsEvalError([] { evaluate("sqrt(-1)"); }));
    CHECK(throwsEvalError([] { evaluate("ln(0)"); }));
    CHECK(throwsEvalError([] { evaluate("sqrt()"); }));

    CHECK(near(evaluate("max(3, 9, 4)"), 9));
    CHECK(near(evaluate("min(3, -9, 4) * 2"), -18));
    CHECK(near(evaluate("max(7)"), 7));
    CHECK(near(evaluate("hypot(3, 4)"), 5));
    CHECK(near(evaluate("pow(2, 10)"), 1024));
    CHECK(near(evaluate("atan2(1, 1) * 4"), 3.14159265358979323846));
    CHECK(near(evaluate("max(1, min(5, 2 + 1))"), 3));
    CHECK(throwsEvalError([] { evaluate("sqrt(1, 2)"); }));
    CHECK(throwsEvalError([] { evaluate("pow(2)"); }));
    CHECK(throwsEvalError([] { evaluate("max(1,)"); }));
    CHECK(throwsEvalError([] { evaluate("5 % 0"); }));
    CHECK(throwsEvalError([] { evaluate("1 / (2 - 2)"); }));
    CHECK(throwsEvalError([] { evaluate(""); }));
    CHECK(throwsEvalError([] { evaluate("1 +"); }));
    CHECK(throwsEvalError([] { evaluate("1 2"); }));
}

int main() {
    testLexer();
    testParser();
    testEvaluator();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
