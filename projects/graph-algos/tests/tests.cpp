#include "graph.hpp"
#include "shortest_paths.hpp"
#include "mst.hpp"
#include "topo.hpp"
#include "scc.hpp"
#include "bridges.hpp"

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

static void test_dijkstra() {
    ga::Graph g(5, true);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 1);
    g.add_edge(2, 1, 2);
    g.add_edge(1, 3, 1);
    g.add_edge(2, 3, 5);
    auto sp = ga::dijkstra(g, 0);
    CHECK((sp.dist[1] == 3 && sp.dist[3] == 4));
    CHECK((sp.path_to(3) == std::vector<int>{0, 2, 1, 3}));
    CHECK(!sp.reachable(4));
    CHECK(sp.path_to(4).empty());
    CHECK((sp.path_to(0) == std::vector<int>{0}));

    ga::Graph neg(2, true);
    neg.add_edge(0, 1, -1);
    CHECK(throws([&] { ga::dijkstra(neg, 0); }));
}

static void test_bellman_ford() {
    ga::Graph g(4, true);
    g.add_edge(0, 1, 5);
    g.add_edge(0, 2, 2);
    g.add_edge(1, 3, 1);
    g.add_edge(2, 1, -4);
    bool neg = true;
    auto sp = ga::bellman_ford(g, 0, neg);
    CHECK(!neg);
    CHECK((sp.dist[1] == -2 && sp.dist[3] == -1));
    CHECK((sp.path_to(3) == std::vector<int>{0, 2, 1, 3}));

    g.add_edge(3, 2, 1);  // 2 -> 1 -> 3 -> 2 has weight -2
    ga::bellman_ford(g, 0, neg);
    CHECK(neg);

    ga::Graph unreachable_cycle(3, true);
    unreachable_cycle.add_edge(1, 2, -1);
    unreachable_cycle.add_edge(2, 1, -1);
    auto sp2 = ga::bellman_ford(unreachable_cycle, 0, neg);
    CHECK(!neg);
    CHECK(!sp2.reachable(1));
}

static void test_topological_sort() {
    // Course prerequisites: 0 -> 2, 1 -> 2, 2 -> 3, 1 -> 4
    ga::Graph g(5, true);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(1, 4);
    auto order = ga::topological_sort(g);
    CHECK(order.has_value());
    CHECK((*order == std::vector<int>{0, 1, 2, 3, 4}));
    CHECK(!ga::has_cycle(g));

    g.add_edge(3, 1);  // 1 -> 2 -> 3 -> 1
    CHECK(!ga::topological_sort(g).has_value());
    CHECK(ga::has_cycle(g));

    ga::Graph self_loop(1, true);
    self_loop.add_edge(0, 0);
    CHECK(ga::has_cycle(self_loop));

    ga::Graph undirected(2);
    CHECK(throws([&] { ga::topological_sort(undirected); }));
}

static void test_disjoint_set() {
    ga::DisjointSet d(5);
    CHECK(d.set_count() == 5);
    CHECK(d.unite(0, 1));
    CHECK(d.unite(1, 2));
    CHECK(!d.unite(0, 2));
    CHECK(d.same(0, 2));
    CHECK(!d.same(0, 3));
    CHECK(d.set_size(2) == 3);
    CHECK(d.set_count() == 3);
}

static void test_kruskal() {
    ga::Graph g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 2, 2);
    g.add_edge(0, 2, 3);
    g.add_edge(2, 3, 4);
    g.add_edge(1, 3, 5);
    auto f = ga::kruskal(g);
    CHECK(f.total_weight == 7);
    CHECK(f.edges.size() == 3);
    CHECK(f.components == 1);

    ga::Graph forest(5);
    forest.add_edge(0, 1, 2);
    forest.add_edge(3, 4, 1);
    auto f2 = ga::kruskal(forest);
    CHECK(f2.total_weight == 3);
    CHECK(f2.components == 3);  // {0,1}, {2}, {3,4}

    ga::Graph directed(2, true);
    CHECK(throws([&] { ga::kruskal(directed); }));
}

static void test_prim() {
    ga::Graph g(5);
    g.add_edge(0, 1, 2);
    g.add_edge(0, 3, 6);
    g.add_edge(1, 2, 3);
    g.add_edge(1, 3, 8);
    g.add_edge(1, 4, 5);
    g.add_edge(2, 4, 7);
    g.add_edge(3, 4, 9);
    auto f = ga::prim(g);
    CHECK(f.total_weight == 16);
    CHECK(f.edges.size() == 4);
    CHECK(f.components == 1);
    CHECK(f.total_weight == ga::kruskal(g).total_weight);

    ga::Graph forest(5);
    forest.add_edge(0, 1, 2);
    forest.add_edge(3, 4, 1);
    auto f2 = ga::prim(forest);
    CHECK(f2.total_weight == 3);
    CHECK(f2.components == 3);

    CHECK(ga::prim(ga::Graph(0)).components == 0);
    ga::Graph directed(2, true);
    CHECK(throws([&] { ga::prim(directed); }));
}

static void test_floyd_warshall() {
    ga::Graph g(4, true);
    g.add_edge(0, 1, 3);
    g.add_edge(0, 3, 7);
    g.add_edge(1, 0, 8);
    g.add_edge(1, 2, 2);
    g.add_edge(2, 0, 5);
    g.add_edge(2, 3, 1);
    g.add_edge(3, 0, 2);
    auto ap = ga::floyd_warshall(g);
    CHECK(!ap.has_negative_cycle);
    CHECK(ap.dist[0][3] == 6);
    CHECK(ap.dist[1][0] == 5);
    CHECK(ap.dist[3][2] == 7);
    CHECK((ap.path(0, 3) == std::vector<int>{0, 1, 2, 3}));
    CHECK((ap.path(2, 2) == std::vector<int>{2}));
    // agrees with Dijkstra from every source
    for (int s = 0; s < 4; ++s) CHECK(ga::dijkstra(g, s).dist == ap.dist[s]);

    ga::Graph split(3, true);
    split.add_edge(0, 1, -2);
    auto ap2 = ga::floyd_warshall(split);
    CHECK(ap2.dist[0][1] == -2);
    CHECK(ap2.dist[1][0] == ga::INF);
    CHECK(ap2.path(0, 2).empty());

    split.add_edge(1, 0, 1);  // cycle weight -1
    CHECK(ga::floyd_warshall(split).has_negative_cycle);
}

static void test_scc() {
    // {0,1,2} cycle -> {3,4} cycle -> 5
    ga::Graph g(6, true);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 3);
    g.add_edge(4, 5);
    auto r = ga::strongly_connected_components(g);
    CHECK(r.count == 3);
    CHECK(r.component[0] == r.component[2]);
    CHECK(r.component[3] == r.component[4]);
    CHECK(r.component[0] != r.component[3]);
    // sinks first: {5} before {3,4} before {0,1,2}
    CHECK(r.component[5] < r.component[3]);
    CHECK(r.component[3] < r.component[0]);
    auto groups = r.groups();
    CHECK((groups[r.component[1]] == std::vector<int>{0, 1, 2}));

    // a long path must not blow the stack and gives n singleton components
    const int n = 200000;
    ga::Graph path(n, true);
    for (int i = 0; i + 1 < n; ++i) path.add_edge(i, i + 1);
    CHECK(ga::strongly_connected_components(path).count == n);

    ga::Graph undirected(2);
    CHECK(throws([&] { ga::strongly_connected_components(undirected); }));
}

static void test_condensation() {
    ga::Graph g(6, true);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 0, 1);
    g.add_edge(1, 2, 7);
    g.add_edge(0, 2, 4);  // parallel to 1 -> 2 after condensing
    g.add_edge(2, 3, 1);
    g.add_edge(3, 2, 1);
    g.add_edge(3, 4, 2);
    g.add_edge(5, 4, 1);
    auto scc = ga::strongly_connected_components(g);
    CHECK(scc.count == 4);
    auto dag = ga::condensation(g, scc);
    CHECK(dag.size() == 4);
    CHECK(dag.edge_count() == 3);
    CHECK(!ga::has_cycle(dag));
    int a = scc.component[0], b = scc.component[2];
    CHECK(dag.neighbors(a).size() == 1);
    CHECK(dag.neighbors(a)[0].to == b);
    CHECK(dag.neighbors(a)[0].weight == 4);
    CHECK(dag.neighbors(scc.component[4]).empty());
}

static void test_cut_structure() {
    // triangle 0-1-2, bridge 1-3, then path 3-4-5
    ga::Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(1, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    auto r = ga::find_cut_structure(g);
    CHECK((r.bridges == std::vector<std::pair<int, int>>{{1, 3}, {3, 4}, {4, 5}}));
    CHECK((r.articulation_points == std::vector<int>{1, 3, 4}));

    ga::Graph cycle(4);
    for (int i = 0; i < 4; ++i) cycle.add_edge(i, (i + 1) % 4);
    auto rc = ga::find_cut_structure(cycle);
    CHECK(rc.bridges.empty());
    CHECK(rc.articulation_points.empty());

    ga::Graph doubled(2);
    doubled.add_edge(0, 1);
    doubled.add_edge(0, 1);
    CHECK(ga::find_cut_structure(doubled).bridges.empty());

    ga::Graph star(4);  // centre 0 is a cut vertex as DFS root
    star.add_edge(0, 1);
    star.add_edge(0, 2);
    star.add_edge(0, 3);
    CHECK((ga::find_cut_structure(star).articulation_points == std::vector<int>{0}));

    ga::Graph directed(2, true);
    CHECK(throws([&] { ga::find_cut_structure(directed); }));
}

int main() {
    test_construction();
    test_traversals();
    test_dijkstra();
    test_bellman_ford();
    test_topological_sort();
    test_disjoint_set();
    test_kruskal();
    test_prim();
    test_floyd_warshall();
    test_scc();
    test_condensation();
    test_cut_structure();
    std::printf("%d passed, %d failed\n", passed, failures);
    return failures == 0 ? 0 : 1;
}
