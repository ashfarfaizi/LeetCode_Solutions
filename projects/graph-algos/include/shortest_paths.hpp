#pragma once

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace ga {

constexpr long long INF = std::numeric_limits<long long>::max() / 4;

struct ShortestPaths {
    std::vector<long long> dist;  // INF when unreachable
    std::vector<int> parent;      // -1 for the source / unreachable vertices

    bool reachable(int v) const { return dist.at(v) != INF; }

    // Vertices on the shortest path from the source to v (empty if unreachable).
    std::vector<int> path_to(int v) const {
        std::vector<int> path;
        if (!reachable(v)) return path;
        for (int cur = v; cur != -1; cur = parent[cur]) path.push_back(cur);
        std::reverse(path.begin(), path.end());
        return path;
    }
};

// Dijkstra with a binary heap. Requires non-negative edge weights.
inline ShortestPaths dijkstra(const Graph& g, int src) {
    ShortestPaths sp{std::vector<long long>(g.size(), INF), std::vector<int>(g.size(), -1)};
    g.neighbors(src);  // validates src
    using Item = std::pair<long long, int>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;
    sp.dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != sp.dist[u]) continue;  // stale heap entry
        for (const auto& e : g.neighbors(u)) {
            if (e.weight < 0) throw std::invalid_argument("dijkstra: negative edge weight");
            long long nd = d + e.weight;
            if (nd < sp.dist[e.to]) {
                sp.dist[e.to] = nd;
                sp.parent[e.to] = u;
                pq.push({nd, e.to});
            }
        }
    }
    return sp;
}

}  // namespace ga
