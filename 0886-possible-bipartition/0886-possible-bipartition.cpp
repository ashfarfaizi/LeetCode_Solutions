/*
 * Approach: treat each dislike pair as an edge and try to two-colour the
 * graph with BFS from every uncoloured person. If an edge ever joins two
 * people of the same colour the split is impossible.
 *
 * Time:  O(n + e), e = dislikes.size()
 * Space: O(n + e)
 */
class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        vector<vector<int>> adj(n + 1);
        for (const auto& d : dislikes) {
            adj[d[0]].push_back(d[1]);
            adj[d[1]].push_back(d[0]);
        }
        vector<int> color(n + 1, -1);
        for (int s = 1; s <= n; ++s) {
            if (color[s] != -1) continue;
            color[s] = 0;
            queue<int> q;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
