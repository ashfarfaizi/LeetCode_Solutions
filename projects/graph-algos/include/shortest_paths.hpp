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

// Bellman-Ford: handles negative weights. Sets has_negative_cycle when a
// negative cycle is reachable from src (distances are then not meaningful).
// Intended for directed graphs; an undirected negative edge is itself a cycle.
inline ShortestPaths bellman_ford(const Graph& g, int src, bool& has_negative_cycle) {
    int n = g.size();
    ShortestPaths sp{std::vector<long long>(n, INF), std::vector<int>(n, -1)};
    g.neighbors(src);
    sp.dist[src] = 0;
    has_negative_cycle = false;
    for (int round = 0; round < n; ++round) {
        bool changed = false;
        for (int u = 0; u < n; ++u) {
            if (sp.dist[u] == INF) continue;
            for (const auto& e : g.neighbors(u)) {
                if (sp.dist[u] + e.weight < sp.dist[e.to]) {
                    sp.dist[e.to] = sp.dist[u] + e.weight;
                    sp.parent[e.to] = u;
                    changed = true;
                }
            }
        }
        if (!changed) return sp;
        if (round == n - 1) has_negative_cycle = true;  // n-th round still relaxed
    }
    return sp;
}

struct AllPairs {
    std::vector<std::vector<long long>> dist;  // INF when unreachable
    std::vector<std::vector<int>> next;        // next hop on a shortest path, -1 if none
    bool has_negative_cycle = false;

    // Vertices on a shortest path from u to v (empty if unreachable or if a
    // negative cycle makes the path undefined).
    std::vector<int> path(int u, int v) const {
        std::vector<int> p;
        if (has_negative_cycle || dist.at(u).at(v) == INF) return p;
        p.push_back(u);
        while (u != v) {
            u = next[u][v];
            p.push_back(u);
        }
        return p;
    }
};

// Floyd-Warshall all-pairs shortest paths, O(V^3) time and O(V^2) memory.
// Negative edges are allowed; a negative cycle sets has_negative_cycle.
inline AllPairs floyd_warshall(const Graph& g) {
    int n = g.size();
    AllPairs ap{std::vector<std::vector<long long>>(n, std::vector<long long>(n, INF)),
                std::vector<std::vector<int>>(n, std::vector<int>(n, -1))};
    for (int u = 0; u < n; ++u) {
        ap.dist[u][u] = 0;
        ap.next[u][u] = u;
        for (const auto& e : g.neighbors(u)) {
            if (e.weight < ap.dist[u][e.to]) {
                ap.dist[u][e.to] = e.weight;
                ap.next[u][e.to] = e.to;
            }
        }
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i) {
            if (ap.dist[i][k] == INF) continue;
            for (int j = 0; j < n; ++j) {
                if (ap.dist[k][j] == INF) continue;
                long long nd = ap.dist[i][k] + ap.dist[k][j];
                if (nd < ap.dist[i][j]) {
                    ap.dist[i][j] = nd;
                    ap.next[i][j] = ap.next[i][k];
                }
            }
        }
    for (int u = 0; u < n; ++u)
        if (ap.dist[u][u] < 0) ap.has_negative_cycle = true;
    return ap;
}

}  // namespace ga
