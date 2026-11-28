/*
 * Approach: greedy. Sort people by (costA - costB); the first half (who save
 * the most by going to A) fly to A, the rest to B.
 * Time: O(n log n)   Space: O(1) extra (in-place sort)
 */
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        sort(costs.begin(), costs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] - a[1] < b[0] - b[1];
        });
        int n = costs.size() / 2, total = 0;
        for (int i = 0; i < n; i++) total += costs[i][0] + costs[i + n][1];
        return total;
    }
};
