#pragma once

#include <algorithm>
#include <limits>
#include <queue>
#include <stdexcept>
#include <vector>

#include "graph.hpp"

namespace ga {

// Maximum flow with Dinic's algorithm: BFS builds a level graph, then DFS
// with per-vertex edge pointers pushes blocking flows. O(V^2 * E) in
// general, much faster on unit-capacity and bipartite networks.
class MaxFlow {
public:
    explicit MaxFlow(int n) {
        if (n < 0) throw std::invalid_argument("size must be non-negative");
        adj_.resize(n);
    }

    // Builds a network from a directed graph, using edge weights as capacities.
    static MaxFlow from_graph(const Graph& g) {
        if (!g.directed()) throw std::invalid_argument("MaxFlow::from_graph: graph must be directed");
        MaxFlow f(g.size());
        for (int u = 0; u < g.size(); ++u)
            for (const auto& e : g.neighbors(u)) f.add_edge(u, e.to, e.weight);
        return f;
    }

    int size() const { return static_cast<int>(adj_.size()); }

    // Adds a directed edge with the given capacity; returns an id for flow_on().
    int add_edge(int u, int v, long long cap) {
        check(u);
        check(v);
        if (cap < 0) throw std::invalid_argument("capacity must be non-negative");
        int fwd = static_cast<int>(adj_[u].size());
        int bwd = static_cast<int>(adj_[v].size()) + (u == v ? 1 : 0);
        adj_[u].push_back({v, bwd, cap, cap});
        adj_[v].push_back({u, fwd, 0, 0});
        handles_.push_back({u, fwd});
        return static_cast<int>(handles_.size()) - 1;
    }

    // Pushes as much additional flow from s to t as possible and returns it.
    long long run(int s, int t) {
        check(s);
        check(t);
        if (s == t) throw std::invalid_argument("source and sink must differ");
        long long total = 0;
        while (bfs(s, t)) {
            it_.assign(size(), 0);
            while (long long f = dfs(s, t, std::numeric_limits<long long>::max())) total += f;
        }
        return total;
    }

    // Flow currently routed through the edge returned by add_edge().
    long long flow_on(int id) const {
        const auto& h = handles_.at(id);
        const auto& e = adj_[h.first][h.second];
        return e.orig - e.cap;
    }

    // After run(): vertices reachable from s in the residual graph. Edges
    // from this set to its complement form a minimum s-t cut.
    std::vector<bool> min_cut_side(int s) const {
        check(s);
        std::vector<bool> seen(size(), false);
        std::queue<int> q;
        seen[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& e : adj_[u])
                if (e.cap > 0 && !seen[e.to]) {
                    seen[e.to] = true;
                    q.push(e.to);
                }
        }
        return seen;
    }

private:
    struct Edge {
        int to;
        int rev;
        long long cap;   // residual capacity
        long long orig;  // original capacity (0 for reverse edges)
    };

    std::vector<std::vector<Edge>> adj_;
    std::vector<std::pair<int, int>> handles_;
    std::vector<int> level_, it_;

    void check(int u) const {
        if (u < 0 || u >= size()) throw std::out_of_range("vertex out of range");
    }

    bool bfs(int s, int t) {
        level_.assign(size(), -1);
        std::queue<int> q;
        level_[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& e : adj_[u])
                if (e.cap > 0 && level_[e.to] < 0) {
                    level_[e.to] = level_[u] + 1;
                    q.push(e.to);
                }
        }
        return level_[t] >= 0;
    }

    long long dfs(int u, int t, long long pushed) {
        if (u == t) return pushed;
        for (int& i = it_[u]; i < static_cast<int>(adj_[u].size()); ++i) {
            Edge& e = adj_[u][i];
            if (e.cap <= 0 || level_[e.to] != level_[u] + 1) continue;
            long long got = dfs(e.to, t, std::min(pushed, e.cap));
            if (got > 0) {
                e.cap -= got;
                adj_[e.to][e.rev].cap += got;
                return got;
            }
        }
        return 0;
    }
};

}  // namespace ga
