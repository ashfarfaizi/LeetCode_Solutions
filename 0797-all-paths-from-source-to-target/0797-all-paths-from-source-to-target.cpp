/*
 * Approach: Depth-first search with backtracking. Keep the current path,
 * record a copy whenever node n - 1 is reached, and undo the step on return.
 * The graph is acyclic, so no visited set is needed.
 * Time: O(2^n * n) in the worst case, Space: O(n) recursion besides output
 */
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> paths;
        vector<int> path = {0};
        dfs(graph, 0, path, paths);
        return paths;
    }

private:
    void dfs(const vector<vector<int>>& g, int u, vector<int>& path, vector<vector<int>>& paths) {
        if (u == (int)g.size() - 1) {
            paths.push_back(path);
            return;
        }
        for (int v : g[u]) {
            path.push_back(v);
            dfs(g, v, path, paths);
            path.pop_back();
        }
    }
};
