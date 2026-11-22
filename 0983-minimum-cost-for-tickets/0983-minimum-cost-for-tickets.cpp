/*
 * Approach: DP over calendar days 1..365. dp[d] is the cheapest way to cover
 * every travel day up to d. On a non-travel day dp[d] = dp[d-1]; on a travel
 * day take the cheapest of buying a 1-, 7- or 30-day pass that ends on day d:
 * dp[d-1] + costs[0], dp[d-7] + costs[1], dp[d-30] + costs[2] (indices
 * clamped at 0).
 *
 * Time:  O(365 + n)
 * Space: O(365)
 */
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int last = days.back();
        vector<bool> travel(last + 1, false);
        for (int d : days) travel[d] = true;
        vector<int> dp(last + 1, 0);
        for (int d = 1; d <= last; ++d) {
            if (!travel[d]) {
                dp[d] = dp[d - 1];
                continue;
            }
            dp[d] = min({dp[d - 1] + costs[0], dp[max(0, d - 7)] + costs[1],
                         dp[max(0, d - 30)] + costs[2]});
        }
        return dp[last];
    }
};
