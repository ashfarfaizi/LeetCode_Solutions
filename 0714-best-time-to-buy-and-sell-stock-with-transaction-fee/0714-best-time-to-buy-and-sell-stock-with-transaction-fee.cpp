/*
 * Approach: Two-state DP. `cash` is the best profit while holding nothing,
 * `hold` is the best profit while holding a share. Each day either keep the
 * state or switch, paying the fee when selling.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int cash = 0, hold = -prices[0];
        for (size_t i = 1; i < prices.size(); ++i) {
            int prevCash = cash;
            cash = max(cash, hold + prices[i] - fee);
            hold = max(hold, prevCash - prices[i]);
        }
        return cash;
    }
};
