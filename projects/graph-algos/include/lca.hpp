#pragma once

#include <stdexcept>
#include <vector>

#include "graph.hpp"

namespace ga {

// Lowest common ancestor on a rooted forest via binary lifting.
// Preprocessing is O(V log V); each query is O(log V). Works on any
// undirected acyclic graph; every component is rooted at its smallest
// vertex unless it contains the explicit root.
class LCA {
public:
    explicit LCA(const Graph& g, int root = 0) : n_(g.size()) {
        if (g.directed()) throw std::invalid_argument("LCA: graph must be undirected");
        if (static_cast<int>(g.edge_count()) >= n_ && n_ > 0)
            throw std::invalid_argument("LCA: graph must be a forest");
        log_ = 1;
        while ((1 << log_) < n_) ++log_;
        up_.assign(log_, std::vector<int>(n_, -1));
        depth_.assign(n_, -1);
        comp_.assign(n_, -1);
        if (n_ == 0) return;
        g.neighbors(root);  // validates root
        int comp = 0;
        build_from(g, root, comp++);
        for (int v = 0; v < n_; ++v)
            if (depth_[v] < 0) build_from(g, v, comp++);
        for (int k = 1; k < log_; ++k)
            for (int v = 0; v < n_; ++v)
                if (up_[k - 1][v] >= 0) up_[k][v] = up_[k - 1][up_[k - 1][v]];
    }

    int depth(int v) const { return depth_.at(v); }
    int parent(int v) const { return up_.empty() ? -1 : up_[0].at(v); }
    bool connected(int u, int v) const { return comp_.at(u) == comp_.at(v); }

    // k-th ancestor of v (0 = v itself), or -1 if it does not exist.
    int ancestor(int v, int k) const {
        check(v);
        if (k < 0) throw std::invalid_argument("LCA::ancestor: k must be non-negative");
        if (k > depth_[v]) return -1;
        for (int b = 0; v >= 0 && k > 0; ++b, k >>= 1)
            if (k & 1) v = up_[b][v];
        return v;
    }

    // Lowest common ancestor, or -1 if u and v are in different trees.
    int query(int u, int v) const {
        check(u);
        check(v);
        if (!connected(u, v)) return -1;
        if (depth_[u] < depth_[v]) std::swap(u, v);
        u = ancestor(u, depth_[u] - depth_[v]);
        if (u == v) return u;
        for (int k = log_ - 1; k >= 0; --k)
            if (up_[k][u] != up_[k][v]) {
                u = up_[k][u];
                v = up_[k][v];
            }
        return up_[0][u];
    }

    // Number of edges on the tree path between u and v (-1 if disconnected).
    int distance(int u, int v) const {
        int a = query(u, v);
        return a < 0 ? -1 : depth_[u] + depth_[v] - 2 * depth_[a];
    }

private:
    int n_;
    int log_ = 1;
    std::vector<std::vector<int>> up_;
    std::vector<int> depth_, comp_;

    void check(int v) const {
        if (v < 0 || v >= n_) throw std::out_of_range("vertex out of range");
    }

    // Iterative DFS so deep trees (paths) do not overflow the stack.
    void build_from(const Graph& g, int root, int comp) {
        std::vector<int> stack{root};
        depth_[root] = 0;
        comp_[root] = comp;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            bool skipped_parent = false;
            for (const auto& e : g.neighbors(u)) {
                if (e.to == u) throw std::invalid_argument("LCA: graph must be a forest");
                if (e.to == up_[0][u] && !skipped_parent) {
                    skipped_parent = true;  // a second edge to the parent is a cycle
                    continue;
                }
                if (depth_[e.to] >= 0) throw std::invalid_argument("LCA: graph must be a forest");
                depth_[e.to] = depth_[u] + 1;
                comp_[e.to] = comp;
                up_[0][e.to] = u;
                stack.push_back(e.to);
            }
        }
    }
};

}  // namespace ga
