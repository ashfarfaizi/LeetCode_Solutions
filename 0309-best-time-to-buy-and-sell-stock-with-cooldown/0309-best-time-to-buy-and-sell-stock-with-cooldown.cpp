#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) return 0;
        
        // Initial states for Day 0
        int hold = -prices[0]; // Profit after buying on day 0
        int sold = 0;          // No stock sold yet
        int rest = 0;          // No transactions made yet
        
        for (size_t i = 1; i < prices.size(); ++i) {
            int prev_sold = sold;
            
            // Update transitions for day i
            sold = hold + prices[i];
            hold = std::max(hold, rest - prices[i]);
            rest = std::max(rest, prev_sold);
        }
        
        // Max profit will be when we aren't holding any stock at the end
        return std::max(sold, rest);
    }
};
