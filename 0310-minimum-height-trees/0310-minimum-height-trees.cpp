/*
 * Approach: Topological trimming. Repeatedly remove all current leaves
 * (degree 1) layer by layer, like peeling an onion. The centroid(s) left
 * when at most two nodes remain are the roots of minimum height trees.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return {0};
        vector<vector<int>> adj(n);
        vector<int> deg(n, 0);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            ++deg[e[0]];
            ++deg[e[1]];
        }
        vector<int> leaves;
        for (int i = 0; i < n; ++i)
            if (deg[i] == 1) leaves.push_back(i);
        int remaining = n;
        while (remaining > 2) {
            remaining -= static_cast<int>(leaves.size());
            vector<int> next;
            for (int leaf : leaves)
                for (int nb : adj[leaf])
                    if (--deg[nb] == 1) next.push_back(nb);
            leaves = move(next);
        }
        return leaves;
    }
};
