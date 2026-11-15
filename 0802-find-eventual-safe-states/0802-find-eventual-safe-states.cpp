/*
 * Approach: Reverse the graph and run Kahn's algorithm from the terminal
 * nodes. A node becomes safe once all of its original out-edges lead to
 * safe nodes, i.e. its out-degree drops to zero. Nodes on or leading into
 * cycles never reach zero.
 * Time: O(V + E), Space: O(V + E)
 */
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> rev(n);
        vector<int> outdeg(n);
        for (int u = 0; u < n; ++u) {
            outdeg[u] = graph[u].size();
            for (int v : graph[u]) rev[v].push_back(u);
        }
        queue<int> q;
        for (int u = 0; u < n; ++u)
            if (outdeg[u] == 0) q.push(u);
        vector<bool> safe(n, false);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            safe[v] = true;
            for (int u : rev[v])
                if (--outdeg[u] == 0) q.push(u);
        }
        vector<int> res;
        for (int u = 0; u < n; ++u)
            if (safe[u]) res.push_back(u);
        return res;
    }
};
