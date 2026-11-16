// Minimal self-contained test runner for cli-todo.
#include "todo.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
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

static bool loadThrows(const std::string& text) {
    std::istringstream in(text);
    try {
        todo::TodoList::load(in);
    } catch (const std::runtime_error&) {
        return true;
    }
    return false;
}

static void testAddAndComplete() {
    todo::TodoList l;
    CHECK(l.add("buy milk") == 1);
    CHECK(l.add("call mum") == 2);
    CHECK(l.tasks().size() == 2);
    CHECK(l.complete(2));
    CHECK(!l.complete(7));
    CHECK(l.find(2)->done);
    CHECK(!l.find(1)->done);
    CHECK(!l.find(3).has_value());
}

static void testSanitizesNewlines() {
    todo::TodoList l;
    l.add("line one\nline two\r");
    CHECK(l.tasks()[0].text == "line one line two ");
}

static void testRoundTrip() {
    todo::TodoList l;
    l.add("first");
    l.add("tab\there");
    l.complete(1);
    std::stringstream ss;
    l.save(ss);
    todo::TodoList r = todo::TodoList::load(ss);
    CHECK(r.tasks().size() == 2);
    CHECK(r.tasks()[0].done && r.tasks()[0].text == "first");
    CHECK(!r.tasks()[1].done && r.tasks()[1].text == "tab\there");
    CHECK(r.nextId() == 3);
}

static void testIdsNotReusedAfterLoad() {
    std::istringstream in("# cli-todo v1\n5\t0\tlate\n");
    todo::TodoList l = todo::TodoList::load(in);
    CHECK(l.add("next") == 6);
}

static void testRejectsMalformed() {
    CHECK(loadThrows("1 0 no tabs\n"));
    CHECK(loadThrows("x\t0\tbad id\n"));
    CHECK(loadThrows("0\t0\tzero id\n"));
    CHECK(loadThrows("1\t2\tbad flag\n"));
    CHECK(loadThrows("1\t0\ta\n1\t0\tduplicate\n"));
    CHECK(!loadThrows("# comment\n\n1\t1\tok\n"));
}

static void testFormat() {
    todo::Task t{3, "write tests", false};
    CHECK(todo::format(t) == "[ ] 3  write tests");
    t.done = true;
    CHECK(todo::format(t) == "[x] 3  write tests");
}

int main() {
    testAddAndComplete();
    testSanitizesNewlines();
    testRoundTrip();
    testIdsNotReusedAfterLoad();
    testRejectsMalformed();
    testFormat();
    std::cout << checks - failures << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
