// Minimal self-contained test runner for lru-cache-lib.
#include "lru_cache.hpp"

#include <iostream>
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

static void testBasicGetPut() {
    lru::LRUCache<int, std::string> c(2);
    CHECK(!c.get(1));
    c.put(1, "one");
    c.put(2, "two");
    CHECK(c.get(1) == std::string("one"));
    CHECK(c.get(2) == std::string("two"));
    CHECK(c.size() == 2);
}

static void testEvictsLeastRecentlyUsed() {
    lru::LRUCache<int, int> c(2);
    c.put(1, 1);
    c.put(2, 2);
    CHECK(c.get(1) == 1);  // 2 is now least recently used
    c.put(3, 3);
    CHECK(!c.get(2));
    CHECK(c.get(1) == 1);
    CHECK(c.get(3) == 3);
    c.put(4, 4);           // evicts 1
    CHECK(!c.get(1));
    CHECK(c.get(3) == 3);
    CHECK(c.get(4) == 4);
}

static void testOverwriteRefreshes() {
    lru::LRUCache<std::string, int> c(2);
    c.put("a", 1);
    c.put("b", 2);
    c.put("a", 10);        // overwrite moves "a" to the front
    c.put("c", 3);         // so "b" is evicted
    CHECK(c.get("a") == 10);
    CHECK(!c.get("b"));
    CHECK(c.size() == 2);
}

static void testZeroCapacityThrows() {
    bool threw = false;
    try {
        lru::LRUCache<int, int> c(0);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    CHECK(threw);
}

int main() {
    testBasicGetPut();
    testEvictsLeastRecentlyUsed();
    testOverwriteRefreshes();
    testZeroCapacityThrows();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
