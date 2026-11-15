#pragma once

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <functional>
#include <queue>
#include <vector>

#include "graph.hpp"

namespace ga {

// Disjoint-set union with path compression and union by size.
class DisjointSet {
public:
    explicit DisjointSet(int n) : parent_(n), size_(n, 1), sets_(n) {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int x) {
        while (parent_[x] != x) {
            parent_[x] = parent_[parent_[x]];  // path halving
            x = parent_[x];
        }
        return x;
    }

    // Returns false if a and b were already in the same set.
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size_[a] < size_[b]) std::swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        --sets_;
        return true;
    }

    bool same(int a, int b) { return find(a) == find(b); }
    int set_size(int x) { return size_[find(x)]; }
    int set_count() const { return sets_; }

private:
    std::vector<int> parent_;
    std::vector<int> size_;
    int sets_;
};

struct SpanningForest {
    long long total_weight = 0;
    std::vector<std::tuple<int, int, long long>> edges;  // u, v, weight
    int components = 0;  // 1 means the forest is a spanning tree
};

// Kruskal's algorithm on an undirected graph. For a disconnected graph the
// result is a minimum spanning forest (one tree per component).
inline SpanningForest kruskal(const Graph& g) {
    if (g.directed()) throw std::invalid_argument("kruskal: graph must be undirected");
    std::vector<std::tuple<long long, int, int>> all;
    for (int u = 0; u < g.size(); ++u)
        for (const auto& e : g.neighbors(u))
            if (u < e.to) all.emplace_back(e.weight, u, e.to);
    std::sort(all.begin(), all.end());

    DisjointSet dsu(g.size());
    SpanningForest f;
    for (const auto& [w, u, v] : all) {
        if (dsu.unite(u, v)) {
            f.total_weight += w;
            f.edges.emplace_back(u, v, w);
        }
    }
    f.components = dsu.set_count();
    return f;
}

// Prim's algorithm with a lazy binary heap, O(E log E). Grows a tree from
// every unvisited vertex in turn, so a disconnected graph yields a minimum
// spanning forest with the same total weight Kruskal would report.
inline SpanningForest prim(const Graph& g) {
    if (g.directed()) throw std::invalid_argument("prim: graph must be undirected");
    using Item = std::tuple<long long, int, int>;  // weight, vertex, parent
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;
    std::vector<bool> in_tree(g.size(), false);
    SpanningForest f;
    for (int s = 0; s < g.size(); ++s) {
        if (in_tree[s]) continue;
        ++f.components;
        pq.emplace(0, s, -1);
        while (!pq.empty()) {
            auto [w, u, p] = pq.top();
            pq.pop();
            if (in_tree[u]) continue;
            in_tree[u] = true;
            if (p != -1) {
                f.total_weight += w;
                f.edges.emplace_back(p, u, w);
            }
            for (const auto& e : g.neighbors(u))
                if (!in_tree[e.to]) pq.emplace(e.weight, e.to, u);
        }
    }
    return f;
}

}  // namespace ga
