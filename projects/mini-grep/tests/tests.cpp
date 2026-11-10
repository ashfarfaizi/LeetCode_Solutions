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

static void testWholeLine() {
    mgrep::Options o;
    o.pattern = "done";
    o.wholeLine = true;
    CHECK(mgrep::Matcher(o).matches("done"));
    CHECK(!mgrep::Matcher(o).matches("done "));
    CHECK(!mgrep::Matcher(o).matches("undone"));
    o.ignoreCase = true;
    CHECK(mgrep::Matcher(o).matches("DONE"));
    o.wholeWord = true;  // -x takes precedence over -w
    CHECK(!mgrep::Matcher(o).matches("all done"));
    o.pattern = "";
    CHECK(mgrep::Matcher(o).matches(""));
    CHECK(!mgrep::Matcher(o).matches("x"));
}

static void testMaxCount() {
    mgrep::Options o;
    o.pattern = "a";
    o.maxCount = 2;
    std::istringstream in("a1\nb\na2\na3\na4\n");
    std::ostringstream out;
    CHECK(mgrep::scan(in, out, mgrep::Matcher(o)) == 2);
    CHECK(out.str() == "a1\na2\n");
    std::string rest;
    std::getline(in, rest);
    CHECK(rest == "a3");  // stopped right after the second match

    o.countOnly = true;
    std::istringstream in2("a\na\na\n");
    std::ostringstream out2;
    CHECK(mgrep::scan(in2, out2, mgrep::Matcher(o)) == 2);
    CHECK(out2.str() == "2\n");

    o.countOnly = false;
    o.maxCount = 0;  // no limit
    std::istringstream in3("a\na\na\n");
    std::ostringstream out3;
    CHECK(mgrep::scan(in3, out3, mgrep::Matcher(o)) == 3);
}

static void testAnyMatch() {
    std::istringstream in("x\nneedle\nmore\n");
    CHECK(mgrep::anyMatch(in, make("needle")));
    std::string rest;
    std::getline(in, rest);
    CHECK(rest == "more");  // stops at the first selected line

    std::istringstream none("x\ny\n");
    CHECK(!mgrep::anyMatch(none, make("needle")));
    std::istringstream empty("");
    CHECK(!mgrep::anyMatch(empty, make("")));

    mgrep::Options o;
    o.pattern = "x";
    o.invert = true;
    std::istringstream allX("x\nxx\n");
    CHECK(!mgrep::anyMatch(allX, mgrep::Matcher(o)));
}

static void testSpans() {
    using Spans = std::vector<std::pair<std::size_t, std::size_t>>;
    CHECK(make("ab").spans("abxab") == (Spans{{0, 2}, {3, 2}}));
    CHECK(make("aa").spans("aaaa") == (Spans{{0, 2}, {2, 2}}));  // non-overlapping
    CHECK(make("ab").spans("xyz").empty());
    CHECK(make("").spans("anything").empty());
    CHECK(make("AB", true).spans("ab Ab") == (Spans{{0, 2}, {3, 2}}));

    mgrep::Options o;
    o.pattern = "cat";
    o.wholeWord = true;
    CHECK(mgrep::Matcher(o).spans("cats cat bobcat cat") == (Spans{{5, 3}, {16, 3}}));
    o.wholeWord = false;
    o.wholeLine = true;
    CHECK(mgrep::Matcher(o).spans("cat") == (Spans{{0, 3}}));
    CHECK(mgrep::Matcher(o).spans("cat ").empty());
}

static void testOnlyMatching() {
    mgrep::Options o;
    o.pattern = "id";
    o.onlyMatching = true;
    o.ignoreCase = true;
    o.lineNumbers = true;
    std::istringstream in("ID=1 id=2\nnone\nuid\n");
    std::ostringstream out;
    CHECK(mgrep::scan(in, out, mgrep::Matcher(o), "f") == 2);  // counts lines
    CHECK(out.str() == "f:1:ID\nf:1:id\nf:3:id\n");

    o.invert = true;  // nothing to print for non-matching lines
    std::istringstream in2("a\nid\n");
    std::ostringstream out2;
    CHECK(mgrep::scan(in2, out2, mgrep::Matcher(o)) == 1);
    CHECK(out2.str().empty());
}

static std::string runScan(const mgrep::Options& o, const std::string& text,
                           const std::string& label = "") {
    std::istringstream in(text);
    std::ostringstream out;
    mgrep::scan(in, out, mgrep::Matcher(o), label);
    return out.str();
}

static void testAfterContext() {
    mgrep::Options o;
    o.pattern = "x";
    o.afterContext = 1;
    // Adjacent groups merge; a gap produces a "--" separator.
    CHECK(runScan(o, "x1\na\nx2\nb\nc\nx3\n") == "x1\na\nx2\nb\n--\nx3\n");

    o.lineNumbers = true;
    CHECK(runScan(o, "x\na\nb\n", "f") == "f:1:x\nf-2-a\n");

    // A match inside the trailing context is printed as a match and extends it.
    o.lineNumbers = false;
    o.afterContext = 2;
    CHECK(runScan(o, "x\nx\na\nb\nc\n") == "x\nx\na\nb\n");

    // -m stops after the trailing context of the last allowed match.
    o.maxCount = 1;
    CHECK(runScan(o, "x\nx\na\nx\n") == "x\nx\na\n");

    // Context is ignored with -c and -o.
    o.maxCount = 0;
    o.countOnly = true;
    CHECK(runScan(o, "x\na\n") == "1\n");
    o.countOnly = false;
    o.onlyMatching = true;
    CHECK(runScan(o, "ax\nb\n") == "x\n");
}

static void testBeforeContext() {
    mgrep::Options o;
    o.pattern = "x";
    o.beforeContext = 2;
    o.lineNumbers = true;
    CHECK(runScan(o, "a\nb\nc\nx\nd\n") == "2-b\n3-c\n4:x\n");
    // Leading context never repeats lines already printed, and gaps get "--".
    CHECK(runScan(o, "a\nx\nb\nx\nc\nd\ne\nf\nx\n") ==
          "1-a\n2:x\n3-b\n4:x\n--\n7-e\n8-f\n9:x\n");
    // Fewer lines than requested at the start of the input.
    CHECK(runScan(o, "x\n") == "1:x\n");
}

static void testBothContexts() {
    mgrep::Options o;
    o.pattern = "x";
    o.beforeContext = 1;
    o.afterContext = 1;
    CHECK(runScan(o, "a\nb\nx\nc\nd\ne\nx\nf\n", "f") ==
          "f-b\nf:x\nf-c\n--\nf-e\nf:x\nf-f\n");
    // Groups that touch are merged without a separator.
    CHECK(runScan(o, "x\na\nb\nx\n") == "x\na\nb\nx\n");
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
    testWholeLine();
    testMaxCount();
    testAnyMatch();
    testSpans();
    testOnlyMatching();
    testAfterContext();
    testBeforeContext();
    testBothContexts();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
