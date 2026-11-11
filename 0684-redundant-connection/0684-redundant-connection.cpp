/*
 * Approach: Union-Find. Process edges in order; the first edge whose two
 * endpoints already share a root closes a cycle. Since the graph is a tree
 * plus one edge, that edge is the last one in input order on the cycle.
 * Time: O(n * alpha(n)), Space: O(n)
 */
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n + 1);
        iota(parent.begin(), parent.end(), 0);
        function<int(int)> find = [&](int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };
        for (auto& e : edges) {
            int a = find(e[0]), b = find(e[1]);
            if (a == b) return e;
            parent[a] = b;
        }
        return {};
    }
};
