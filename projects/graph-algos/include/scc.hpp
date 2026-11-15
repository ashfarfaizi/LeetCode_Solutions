#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace ga {

struct SCCResult {
    int count = 0;
    std::vector<int> component;  // component id per vertex, 0..count-1

    // Vertices grouped by component, each group sorted ascending.
    std::vector<std::vector<int>> groups() const {
        std::vector<std::vector<int>> out(count);
        for (int v = 0; v < static_cast<int>(component.size()); ++v)
            out[component[v]].push_back(v);
        return out;
    }
};

// Tarjan's strongly connected components, iterative so deep graphs do not
// overflow the call stack. O(V + E). Component ids come out in reverse
// topological order of the condensation (sinks first).
inline SCCResult strongly_connected_components(const Graph& g) {
    if (!g.directed())
        throw std::invalid_argument("strongly_connected_components: graph must be directed");
    int n = g.size();
    std::vector<int> index(n, -1), low(n, 0);
    std::vector<bool> on_stack(n, false);
    std::vector<int> stack;
    std::vector<std::pair<int, std::size_t>> call;  // vertex, next edge index
    SCCResult r;
    r.component.assign(n, -1);
    int timer = 0;

    for (int s = 0; s < n; ++s) {
        if (index[s] != -1) continue;
        call.push_back({s, 0});
        index[s] = low[s] = timer++;
        stack.push_back(s);
        on_stack[s] = true;
        while (!call.empty()) {
            auto& [u, i] = call.back();
            const auto& nb = g.neighbors(u);
            if (i < nb.size()) {
                int v = nb[i++].to;
                if (index[v] == -1) {
                    index[v] = low[v] = timer++;
                    stack.push_back(v);
                    on_stack[v] = true;
                    call.push_back({v, 0});
                } else if (on_stack[v]) {
                    low[u] = std::min(low[u], index[v]);
                }
                continue;
            }
            int done = u;
            call.pop_back();
            if (!call.empty()) {
                int parent = call.back().first;
                low[parent] = std::min(low[parent], low[done]);
            }
            if (low[done] == index[done]) {
                int w;
                do {
                    w = stack.back();
                    stack.pop_back();
                    on_stack[w] = false;
                    r.component[w] = r.count;
                } while (w != done);
                ++r.count;
            }
        }
    }
    return r;
}

}  // namespace ga
