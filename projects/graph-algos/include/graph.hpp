#pragma once

#include <cstddef>
#include <queue>
#include <stdexcept>
#include <vector>

namespace ga {

// Weighted graph stored as adjacency lists. Vertices are 0..n-1.
// Undirected graphs store each edge in both directions.
class Graph {
public:
    struct Edge {
        int to;
        long long weight;
    };

    explicit Graph(int n, bool directed = false)
        : adj_(check_size(n)), directed_(directed) {}

    int size() const { return static_cast<int>(adj_.size()); }
    bool directed() const { return directed_; }
    std::size_t edge_count() const { return edges_; }

    void add_edge(int u, int v, long long w = 1) {
        check_vertex(u);
        check_vertex(v);
        adj_[u].push_back({v, w});
        if (!directed_ && u != v) adj_[v].push_back({u, w});
        ++edges_;
    }

    const std::vector<Edge>& neighbors(int u) const {
        check_vertex(u);
        return adj_[u];
    }

private:
    std::vector<std::vector<Edge>> adj_;
    bool directed_;
    std::size_t edges_ = 0;

    static std::size_t check_size(int n) {
        if (n < 0) throw std::invalid_argument("graph size must be non-negative");
        return static_cast<std::size_t>(n);
    }
    void check_vertex(int u) const {
        if (u < 0 || u >= size()) throw std::out_of_range("vertex out of range");
    }
};

// Visit order of a breadth-first search starting at src.
inline std::vector<int> bfs_order(const Graph& g, int src) {
    std::vector<bool> seen(g.size(), false);
    std::vector<int> order;
    std::queue<int> q;
    g.neighbors(src);  // validates src
    seen[src] = true;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (const auto& e : g.neighbors(u)) {
            if (!seen[e.to]) {
                seen[e.to] = true;
                q.push(e.to);
            }
        }
    }
    return order;
}

// Unweighted hop distance from src to each vertex (-1 if unreachable).
inline std::vector<int> bfs_distances(const Graph& g, int src) {
    std::vector<int> dist(g.size(), -1);
    std::queue<int> q;
    g.neighbors(src);
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& e : g.neighbors(u)) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + 1;
                q.push(e.to);
            }
        }
    }
    return dist;
}

// Pre-order of an iterative depth-first search that visits neighbours in
// insertion order (matching the recursive formulation).
inline std::vector<int> dfs_order(const Graph& g, int src) {
    std::vector<bool> seen(g.size(), false);
    std::vector<int> order;
    std::vector<std::pair<int, std::size_t>> stack;  // vertex, next edge index
    g.neighbors(src);
    seen[src] = true;
    order.push_back(src);
    stack.push_back({src, 0});
    while (!stack.empty()) {
        auto& [u, i] = stack.back();
        const auto& nb = g.neighbors(u);
        if (i == nb.size()) {
            stack.pop_back();
            continue;
        }
        int v = nb[i++].to;
        if (!seen[v]) {
            seen[v] = true;
            order.push_back(v);
            stack.push_back({v, 0});
        }
    }
    return order;
}

// Label each vertex with its connected component id (undirected sense).
// Returns the number of components; labels are 0..count-1.
inline int connected_components(const Graph& g, std::vector<int>& label) {
    label.assign(g.size(), -1);
    int count = 0;
    for (int s = 0; s < g.size(); ++s) {
        if (label[s] != -1) continue;
        for (int v : bfs_order(g, s)) label[v] = count;
        ++count;
    }
    return count;
}

// Two-colour the graph (undirected sense) with BFS. Returns true and fills
// side with 0/1 per vertex if the graph is bipartite; otherwise returns false
// and side is left empty. Self-loops and odd cycles make it non-bipartite.
inline bool is_bipartite(const Graph& g, std::vector<int>& side) {
    if (g.directed()) throw std::invalid_argument("is_bipartite: graph must be undirected");
    side.assign(g.size(), -1);
    std::queue<int> q;
    for (int s = 0; s < g.size(); ++s) {
        if (side[s] != -1) continue;
        side[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& e : g.neighbors(u)) {
                if (side[e.to] == -1) {
                    side[e.to] = side[u] ^ 1;
                    q.push(e.to);
                } else if (side[e.to] == side[u]) {
                    side.clear();
                    return false;
                }
            }
        }
    }
    return true;
}

}  // namespace ga
