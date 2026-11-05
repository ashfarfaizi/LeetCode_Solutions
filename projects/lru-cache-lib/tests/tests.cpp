// Minimal self-contained test runner for lru-cache-lib.
#include "lru_cache.hpp"

#include <iostream>
#include <string>
#include <vector>

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

static void testPeekDoesNotRefresh() {
    lru::LRUCache<int, int> c(2);
    c.put(1, 1);
    c.put(2, 2);
    CHECK(c.peek(1) == 1);  // 1 stays least recently used
    CHECK(c.contains(1));
    c.put(3, 3);
    CHECK(!c.contains(1));
    CHECK(!c.peek(1));
    CHECK(c.contains(2));
}

static void testEraseAndClear() {
    lru::LRUCache<int, int> c(3);
    c.put(1, 1);
    c.put(2, 2);
    CHECK(c.erase(1));
    CHECK(!c.erase(1));
    CHECK(c.size() == 1);
    c.put(3, 3);
    c.put(4, 4);
    c.put(5, 5);           // full again only now, evicts 2
    CHECK(!c.contains(2));
    c.clear();
    CHECK(c.empty());
    c.put(6, 6);
    CHECK(c.get(6) == 6);
}

static void testStats() {
    lru::LRUCache<int, int> c(2);
    CHECK(c.stats().hitRate() == 0.0);
    c.put(1, 1);
    c.put(2, 2);
    c.get(1);              // hit
    c.get(3);              // miss
    c.peek(2);             // not counted
    c.put(3, 3);           // evicts 2
    c.put(4, 4);           // evicts 1
    CHECK(c.stats().hits == 1);
    CHECK(c.stats().misses == 1);
    CHECK(c.stats().evictions == 2);
    CHECK(c.stats().hitRate() == 0.5);
    c.resetStats();
    CHECK(c.stats().hits == 0 && c.stats().evictions == 0);
}

static void testEvictionCallback() {
    std::vector<std::pair<int, std::string>> evicted;
    lru::LRUCache<int, std::string> c(2, [&](const int& k, const std::string& v) {
        evicted.emplace_back(k, v);
    });
    c.put(1, "a");
    c.put(2, "b");
    c.get(1);
    c.put(3, "c");         // evicts 2
    c.erase(1);            // explicit erase: no callback
    c.put(4, "d");
    c.put(5, "e");         // evicts 3
    CHECK(evicted.size() == 2);
    CHECK(evicted[0] == std::make_pair(2, std::string("b")));
    CHECK(evicted[1] == std::make_pair(3, std::string("c")));

    int count = 0;
    c.setEvictionCallback([&](const int&, const std::string&) { ++count; });
    c.put(6, "f");
    CHECK(count == 1);
    CHECK(evicted.size() == 2);
}

int main() {
    testBasicGetPut();
    testEvictsLeastRecentlyUsed();
    testOverwriteRefreshes();
    testZeroCapacityThrows();
    testPeekDoesNotRefresh();
    testEraseAndClear();
    testStats();
    testEvictionCallback();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
