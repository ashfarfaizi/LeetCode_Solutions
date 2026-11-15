#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace ga {

struct CutStructure {
    std::vector<std::pair<int, int>> bridges;  // (u, v) with u < v, sorted
    std::vector<int> articulation_points;      // sorted ascending
};

// Bridges and articulation points of an undirected graph via low-link DFS,
// O(V + E), iterative. Parallel edges are handled by skipping only the one
// edge we arrived through (by its index), so a doubled edge is never a bridge.
inline CutStructure find_cut_structure(const Graph& g) {
    if (g.directed()) throw std::invalid_argument("find_cut_structure: graph must be undirected");
    int n = g.size();
    std::vector<int> tin(n, -1), low(n, 0), parent_edge(n, -1), parent(n, -1);
    std::vector<bool> is_cut(n, false);
    // Neighbour lists hold both directions; pair each entry with an edge id
    // so the reverse of the tree edge can be recognised.
    std::vector<std::vector<std::pair<int, int>>> adj(n);  // to, edge id
    {
        int id = 0;
        for (int u = 0; u < n; ++u)
            for (const auto& e : g.neighbors(u)) {
                if (u < e.to) {
                    adj[u].push_back({e.to, id});
                    adj[e.to].push_back({u, id});
                    ++id;
                }
            }
    }
    CutStructure r;
    int timer = 0;
    std::vector<std::pair<int, std::size_t>> call;
    for (int s = 0; s < n; ++s) {
        if (tin[s] != -1) continue;
        int root_children = 0;
        tin[s] = low[s] = timer++;
        call.push_back({s, 0});
        while (!call.empty()) {
            auto& [u, i] = call.back();
            if (i < adj[u].size()) {
                auto [v, id] = adj[u][i++];
                if (id == parent_edge[u]) continue;
                if (tin[v] == -1) {
                    parent[v] = u;
                    parent_edge[v] = id;
                    tin[v] = low[v] = timer++;
                    if (u == s) ++root_children;
                    call.push_back({v, 0});
                } else {
                    low[u] = std::min(low[u], tin[v]);
                }
                continue;
            }
            int v = u;
            call.pop_back();
            int p = parent[v];
            if (p == -1) continue;
            low[p] = std::min(low[p], low[v]);
            if (low[v] > tin[p]) r.bridges.push_back({std::min(p, v), std::max(p, v)});
            if (p != s && low[v] >= tin[p]) is_cut[p] = true;
        }
        if (root_children > 1) is_cut[s] = true;
    }
    std::sort(r.bridges.begin(), r.bridges.end());
    for (int v = 0; v < n; ++v)
        if (is_cut[v]) r.articulation_points.push_back(v);
    return r;
}

}  // namespace ga
