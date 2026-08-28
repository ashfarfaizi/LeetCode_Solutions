#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        // Optimization: if k is larger than max possible transactions,
        // grab all profitable upstream price movements greedly.
        if (k >= n / 2) {
            int max_profit = 0;
            for (int i = 1; i < n; ++i) {
                if (prices[i] > prices[i - 1]) {
                    max_profit += prices[i] - prices[i - 1];
                }
            }
            return max_profit;
        }

        // DP state arrays initialized for k transactions
        vector<int> buy(k + 1, INT_MIN);
        vector<int> sell(k + 1, 0);

        for (int price : prices) {
            for (int j = 1; j <= k; ++j) {
                // j-th buy depends on previous transaction's sell minus current price
                buy[j] = max(buy[j], sell[j - 1] - price);
                // j-th sell depends on current buy state plus current price
                sell[j] = max(sell[j], buy[j] + price);
            }
        }

        return sell[k];
    }
};
