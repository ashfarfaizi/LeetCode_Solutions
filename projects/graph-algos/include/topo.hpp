#pragma once

#include <optional>
#include <queue>
#include <stdexcept>
#include <vector>

#include "graph.hpp"

namespace ga {

// Kahn's algorithm. Returns a topological order of a directed graph, or
// std::nullopt if the graph contains a cycle. Among vertices that become
// ready at the same time, smaller ids come first (deterministic output).
inline std::optional<std::vector<int>> topological_sort(const Graph& g) {
    if (!g.directed()) throw std::invalid_argument("topological_sort: graph must be directed");
    int n = g.size();
    std::vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (const auto& e : g.neighbors(u)) ++indeg[e.to];

    std::priority_queue<int, std::vector<int>, std::greater<int>> ready;
    for (int u = 0; u < n; ++u)
        if (indeg[u] == 0) ready.push(u);

    std::vector<int> order;
    order.reserve(n);
    while (!ready.empty()) {
        int u = ready.top();
        ready.pop();
        order.push_back(u);
        for (const auto& e : g.neighbors(u))
            if (--indeg[e.to] == 0) ready.push(e.to);
    }
    if (static_cast<int>(order.size()) != n) return std::nullopt;
    return order;
}

inline bool has_cycle(const Graph& g) { return !topological_sort(g).has_value(); }

}  // namespace ga
