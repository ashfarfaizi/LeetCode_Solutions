
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // State variables tracking the effective cost and maximum profit
        // for the first and second transactions.
        int buy1 = INT_MAX;
        int profit1 = 0;
        int buy2 = INT_MAX;
        int profit2 = 0;
        
        for (int price : prices) {
            // Transaction 1: Standard max profit tracking
            buy1 = min(buy1, price);
            profit1 = max(profit1, price - buy1);
            
            // Transaction 2: Reinvesting profit1. 
            // We treat the net effective cost of buy2 as (price - profit1).
            buy2 = min(buy2, price - profit1);
            profit2 = max(profit2, price - buy2);
        }
        
        return profit2;
    }
};
