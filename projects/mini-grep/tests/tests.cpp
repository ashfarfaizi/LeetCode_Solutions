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

static void testLineNumbers() {
    mgrep::Options o;
    o.pattern = "a";
    o.lineNumbers = true;
    std::istringstream in("a1\nb2\na3\n");
    std::ostringstream out;
    CHECK(mgrep::scan(in, out, mgrep::Matcher(o), "x") == 2);
    CHECK(out.str() == "x:1:a1\nx:3:a3\n");
}

static void testCountOnly() {
    mgrep::Options o;
    o.pattern = "a";
    o.countOnly = true;
    o.lineNumbers = true;  // ignored when counting
    std::istringstream in("a\nb\na\na\n");
    std::ostringstream out;
    CHECK(mgrep::scan(in, out, mgrep::Matcher(o)) == 3);
    CHECK(out.str() == "3\n");

    std::istringstream none("b\n");
    std::ostringstream out2;
    CHECK(mgrep::scan(none, out2, mgrep::Matcher(o), "f") == 0);
    CHECK(out2.str() == "f:0\n");
}

static void testInvert() {
    mgrep::Options o;
    o.pattern = "#";
    o.invert = true;
    mgrep::Matcher m(o);
    CHECK(m.matches("key = value"));
    CHECK(!m.matches("# comment"));
    std::istringstream in("# a\nx\n# b\ny\n");
    std::ostringstream out;
    CHECK(mgrep::scan(in, out, m) == 2);
    CHECK(out.str() == "x\ny\n");
}

static void testWholeWord() {
    mgrep::Options o;
    o.pattern = "cat";
    o.wholeWord = true;
    mgrep::Matcher m(o);
    CHECK(m.matches("cat"));
    CHECK(m.matches("the cat sat"));
    CHECK(m.matches("(cat)"));
    CHECK(!m.matches("concatenate"));
    CHECK(!m.matches("cats"));
    CHECK(!m.matches("cat_food"));
    CHECK(m.matches("cats and a cat"));  // a later occurrence qualifies

    o.ignoreCase = true;
    CHECK(mgrep::Matcher(o).matches("Cat!"));
    o.invert = true;
    CHECK(mgrep::Matcher(o).matches("bobcat"));
}

int main() {
    testLiteralMatch();
    testIgnoreCase();
    testScan();
    testScanWithLabel();
    testLineNumbers();
    testCountOnly();
    testInvert();
    testWholeWord();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
