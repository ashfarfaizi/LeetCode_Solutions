#pragma GCC optimize ("O2")

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Track the lowest price seen so far, initialized to infinity
        int minPrice = INT_MAX;
        // Track the maximum profit that can be achieved
        int maxProfitSoFar = 0;
        
        // Loop through prices day by day
        for (int price : prices) {
            // Update the minimum buying price if the current day is lower
            if (price < minPrice) {
                minPrice = price;
            } 
            // Calculate potential profit if sold today and update maxProfitSoFar
            else if (price - minPrice > maxProfitSoFar) {
                maxProfitSoFar = price - minPrice;
            }
        }
        
        return maxProfitSoFar;
    }
};
