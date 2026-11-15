/*
 * Approach: Bellman-Ford limited to k + 1 rounds. Each round relaxes every
 * flight using a copy of the previous round's costs, so a round adds at most
 * one edge to any path and the stop limit is respected.
 * Time: O(k * E), Space: O(n)
 */
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int INF = INT_MAX;
        vector<int> cost(n, INF);
        cost[src] = 0;
        for (int round = 0; round <= k; ++round) {
            vector<int> next = cost;
            for (const auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (cost[u] != INF && cost[u] + w < next[v]) next[v] = cost[u] + w;
            }
            cost = move(next);
        }
        return cost[dst] == INF ? -1 : cost[dst];
    }
};
