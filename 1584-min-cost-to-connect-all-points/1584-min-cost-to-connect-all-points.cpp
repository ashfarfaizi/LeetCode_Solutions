/*
 * Approach: Dense-graph Prim's algorithm. The graph is complete, so instead
 * of a heap keep dist[v] = cheapest edge from the growing tree to v and pick
 * the closest unvisited point by linear scan each round, then relax all
 * remaining points against it.
 *
 * Time:  O(n^2)
 * Space: O(n)
 */
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> dist(n, INT_MAX);
        vector<bool> inTree(n, false);
        dist[0] = 0;
        int total = 0;
        for (int round = 0; round < n; ++round) {
            int u = -1;
            for (int v = 0; v < n; ++v)
                if (!inTree[v] && (u == -1 || dist[v] < dist[u])) u = v;
            inTree[u] = true;
            total += dist[u];
            for (int v = 0; v < n; ++v) {
                if (inTree[v]) continue;
                int d = abs(points[u][0] - points[v][0]) +
                        abs(points[u][1] - points[v][1]);
                dist[v] = min(dist[v], d);
            }
        }
        return total;
    }
};
