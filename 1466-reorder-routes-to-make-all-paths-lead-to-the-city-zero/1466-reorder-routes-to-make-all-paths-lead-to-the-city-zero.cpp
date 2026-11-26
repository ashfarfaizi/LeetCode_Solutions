/*
 * Approach: build an undirected adjacency list where each edge remembers
 * whether it points away from the neighbour we traverse from. BFS from city
 * 0 outwards; every original edge that points away from 0 must be flipped.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<pair<int, int>>> adj(n);  // (neighbour, cost to use)
        for (auto& c : connections) {
            adj[c[0]].push_back({c[1], 1});  // original a -> b points away
            adj[c[1]].push_back({c[0], 0});
        }
        vector<bool> seen(n, false);
        queue<int> q;
        q.push(0);
        seen[0] = true;
        int flips = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, cost] : adj[u]) {
                if (seen[v]) continue;
                seen[v] = true;
                flips += cost;
                q.push(v);
            }
        }
        return flips;
    }
};
