#include "graph.hpp"

#include <cstdio>
#include <functional>
#include <string>
#include <vector>

static int failures = 0;
static int passed = 0;

#define CHECK(cond)                                                     \
    do {                                                                \
        if (cond) {                                                     \
            ++passed;                                                   \
        } else {                                                        \
            ++failures;                                                 \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        }                                                               \
    } while (0)

static bool throws(const std::function<void()>& f) {
    try {
        f();
    } catch (...) {
        return true;
    }
    return false;
}

static void test_construction() {
    ga::Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2, 5);
    CHECK(g.size() == 4);
    CHECK(g.edge_count() == 2);
    CHECK(g.neighbors(1).size() == 2);
    CHECK(g.neighbors(2)[0].weight == 5);

    ga::Graph d(3, true);
    d.add_edge(0, 1);
    CHECK(d.neighbors(0).size() == 1);
    CHECK(d.neighbors(1).empty());

    CHECK(throws([&] { g.add_edge(0, 4); }));
    CHECK(throws([] { ga::Graph bad(-1); }));
}

static void test_traversals() {
    // 0 - 1 - 3
    // |   |
    // 2 --+     4 (isolated)
    ga::Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 2);
    CHECK((ga::bfs_order(g, 0) == std::vector<int>{0, 1, 2, 3}));
    CHECK((ga::dfs_order(g, 0) == std::vector<int>{0, 1, 3, 2}));
    CHECK((ga::bfs_distances(g, 0) == std::vector<int>{0, 1, 1, 2, -1}));
    CHECK((ga::bfs_order(g, 4) == std::vector<int>{4}));

    std::vector<int> label;
    CHECK(ga::connected_components(g, label) == 2);
    CHECK(label[0] == label[3]);
    CHECK(label[4] != label[0]);
}

int main() {
    test_construction();
    test_traversals();
    std::printf("%d passed, %d failed\n", passed, failures);
    return failures == 0 ? 0 : 1;
}
