/*
 * Approach: Bottom-up DP keeping only the last two values: the cheapest cost
 * to reach step i is min(reach[i-1] + cost[i-1], reach[i-2] + cost[i-2]).
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int prev2 = 0, prev1 = 0;  // cheapest cost to reach steps i-2 and i-1
        for (int i = 2; i <= (int)cost.size(); ++i) {
            int cur = min(prev1 + cost[i - 1], prev2 + cost[i - 2]);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
};
