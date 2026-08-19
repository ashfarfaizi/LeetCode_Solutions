
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfitTotal = 0;
        
        // Loop through the prices starting from the second day (index 1)
        for (size_t i = 1; i < prices.size(); ++i) {
            // Whenever the price today is higher than yesterday, 
            // accumulate the immediate profit segment.
            if (prices[i] > prices[i - 1]) {
                maxProfitTotal += prices[i] - prices[i - 1];
            }
        }
        
        return maxProfitTotal;
    }
};
