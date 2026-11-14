/*
 * Approach: Two-colour each connected component with BFS. Every neighbour
 * must receive the opposite colour of the current node; finding a neighbour
 * already painted the same colour means an odd cycle, so not bipartite.
 * Time: O(V + E), Space: O(V)
 */
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1);
        for (int start = 0; start < n; ++start) {
            if (color[start] != -1) continue;
            queue<int> q;
            q.push(start);
            color[start] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : graph[u]) {
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
