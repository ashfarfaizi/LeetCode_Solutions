// Minimal self-contained test runner for mini-grep.
#include "grep.hpp"

#include <iostream>
#include <sstream>
#include <string>

static int failures = 0;
static int checks = 0;

#define CHECK(cond)                                                          \
    do {                                                                     \
        ++checks;                                                            \
        if (!(cond)) {                                                       \
            ++failures;                                                      \
            std::cerr << __FILE__ << ":" << __LINE__ << ": FAILED: " #cond "\n"; \
        }                                                                    \
    } while (0)

static mgrep::Matcher make(const std::string& pattern, bool ignoreCase = false) {
    mgrep::Options o;
    o.pattern = pattern;
    o.ignoreCase = ignoreCase;
    return mgrep::Matcher(o);
}

static void testLiteralMatch() {
    auto m = make("err");
    CHECK(m.matches("error: disk full"));
    CHECK(m.matches("an err here"));
    CHECK(!m.matches("ERROR"));
    CHECK(!m.matches(""));
    CHECK(make("").matches("anything"));  // empty pattern matches every line
}

static void testIgnoreCase() {
    auto m = make("ErR", true);
    CHECK(m.matches("ERROR"));
    CHECK(m.matches("error"));
    CHECK(!m.matches("e r r"));
}

static void testScan() {
    std::istringstream in("alpha\nbeta\ngamma\nalphabet\n");
    std::ostringstream out;
    CHECK(mgrep::scan(in, out, make("alpha")) == 2);
    CHECK(out.str() == "alpha\nalphabet\n");
}

static void testScanWithLabel() {
    std::istringstream in("one\ntwo\nthree");  // last line has no newline
    std::ostringstream out;
    CHECK(mgrep::scan(in, out, make("t"), "f.txt") == 2);
    CHECK(out.str() == "f.txt:two\nf.txt:three\n");
}

int main() {
    testLiteralMatch();
    testIgnoreCase();
    testScan();
    testScanWithLabel();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
