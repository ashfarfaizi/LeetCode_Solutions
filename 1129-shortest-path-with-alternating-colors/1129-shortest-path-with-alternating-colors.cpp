/*
 * Approach: BFS over states (node, colour of the last edge used). From a
 * state reached by a red edge we may only follow blue edges and vice versa.
 * Start from node 0 with both "last colour" states at distance 0; the answer
 * for a node is the first time either of its states is reached.
 *
 * Time:  O(n + red + blue)
 * Space: O(n + red + blue)
 */
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges,
                                         vector<vector<int>>& blueEdges) {
        vector<vector<int>> adj[2];  // adj[0] red, adj[1] blue
        adj[0].assign(n, {});
        adj[1].assign(n, {});
        for (auto& e : redEdges) adj[0][e[0]].push_back(e[1]);
        for (auto& e : blueEdges) adj[1][e[0]].push_back(e[1]);

        vector<array<bool, 2>> seen(n, {false, false});
        vector<int> ans(n, -1);
        queue<pair<int, int>> q;  // node, colour of next edge to take
        q.push({0, 0});
        q.push({0, 1});
        seen[0] = {true, true};
        for (int dist = 0; !q.empty(); ++dist) {
            for (int sz = q.size(); sz > 0; --sz) {
                auto [u, color] = q.front();
                q.pop();
                if (ans[u] == -1) ans[u] = dist;
                for (int v : adj[color][u]) {
                    int next = color ^ 1;
                    if (seen[v][next]) continue;
                    seen[v][next] = true;
                    q.push({v, next});
                }
            }
        }
        return ans;
    }
};
