class Solution {
public:
    int getMoneyAmount(int n) {
        // dp[i][j] will store the minimum money needed to guarantee a win for range [i, j]
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        
        // Loop over the length of the interval (from 2 up to n)
        for (int len = 2; len <= n; ++len) {
            for (int i = 1; i <= n - len + 1; ++i) {
                int j = i + len - 1;
                int min_cost = INT_MAX;
                
                // Try every possible guess x inside the range [i, j]
                for (int x = i; x <= j; ++x) {
                    int cost = x + max(dp[i][x - 1], dp[x + 1][j]);
                    min_cost = min(min_cost, cost);
                }
                dp[i][j] = min_cost;
            }
        }
        
        return dp[1][n];
    }
};
