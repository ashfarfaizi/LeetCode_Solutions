#pragma once

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <tuple>
#include <utility>
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

}  // namespace ga
