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

static void testRemoveAndEdit() {
    todo::TodoList l;
    l.add("a");
    l.add("b");
    l.add("c");
    CHECK(l.remove(2));
    CHECK(!l.remove(2));
    CHECK(l.tasks().size() == 2);
    CHECK(l.tasks()[1].id == 3);
    CHECK(l.add("d") == 4);  // removed id 2 is not reused
    CHECK(l.edit(1, "alpha\nbeta"));
    CHECK(l.find(1)->text == "alpha beta");
    CHECK(!l.edit(2, "gone"));
}

static void testPriorities() {
    CHECK(todo::parsePriority("high") == todo::Priority::High);
    CHECK(todo::parsePriority("l") == todo::Priority::Low);
    CHECK(!todo::parsePriority("urgent").has_value());

    todo::TodoList l;
    l.add("normal a");
    l.add("low", todo::Priority::Low);
    l.add("high", todo::Priority::High);
    l.add("normal b");
    auto s = l.sorted();
    CHECK(s[0].id == 3 && s[1].id == 1 && s[2].id == 4 && s[3].id == 2);
    CHECK(l.tasks()[0].id == 1);  // storage order is untouched
    CHECK(l.setPriority(4, todo::Priority::High));
    CHECK(!l.setPriority(9, todo::Priority::High));
    CHECK(l.sorted()[1].id == 4);

    std::stringstream ss;
    l.save(ss);
    todo::TodoList r = todo::TodoList::load(ss);
    CHECK(r.find(2)->priority == todo::Priority::Low);
    CHECK(r.find(3)->priority == todo::Priority::High);
    CHECK(r.find(1)->priority == todo::Priority::Normal);
}

static void testLoadsV1Files() {
    std::istringstream in("# cli-todo v1\n1\t0\tH\tlooks like v2\n");
    todo::TodoList l = todo::TodoList::load(in);
    CHECK(l.find(1)->text == "H\tlooks like v2");
    CHECK(l.find(1)->priority == todo::Priority::Normal);
    CHECK(loadThrows("# cli-todo v2\n1\t0\tX\tbad level\n"));
    CHECK(loadThrows("# cli-todo v2\n1\t0\tno level\n"));
}

static void testClearDone() {
    todo::TodoList l;
    l.add("a");
    l.add("b");
    l.add("c");
    CHECK(l.clearDone() == 0);
    l.complete(1);
    l.complete(3);
    CHECK(l.clearDone() == 2);
    CHECK(l.tasks().size() == 1 && l.tasks()[0].id == 2);
    CHECK(l.add("d") == 4);
}

static void testReopen() {
    todo::TodoList l;
    l.add("a");
    l.complete(1);
    CHECK(l.reopen(1));
    CHECK(!l.find(1)->done);
    CHECK(l.reopen(1));  // already pending: still succeeds, stays pending
    CHECK(!l.find(1)->done);
    CHECK(!l.reopen(2));
}

static void testSearch() {
    todo::TodoList l;
    l.add("Buy milk");
    l.add("call mum");
    l.add("buy bread", todo::Priority::High);
    auto hits = l.search("BUY");
    CHECK(hits.size() == 2);
    CHECK(hits[0].id == 3 && hits[1].id == 1);  // display order
    CHECK(l.search("mum").size() == 1);
    CHECK(l.search("xyz").empty());
    CHECK(l.search("").size() == 3);
}

static void testFormat() {
    todo::Task t{3, "write tests", false};
    CHECK(todo::format(t) == "[ ] 3  write tests");
    t.done = true;
    CHECK(todo::format(t) == "[x] 3  write tests");
    t.priority = todo::Priority::High;
    CHECK(todo::format(t) == "[x] 3  (high) write tests");
}

int main() {
    testAddAndComplete();
    testSanitizesNewlines();
    testRoundTrip();
    testIdsNotReusedAfterLoad();
    testRejectsMalformed();
    testRemoveAndEdit();
    testPriorities();
    testLoadsV1Files();
    testClearDone();
    testReopen();
    testSearch();
    testFormat();
    std::cout << checks - failures << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
