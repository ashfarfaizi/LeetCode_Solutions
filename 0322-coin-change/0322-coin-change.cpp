class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // Create a DP array initialized with a value greater than any possible answer
        vector<int> dp(amount + 1, amount + 1);
        
        // Base case: 0 coins are needed to make an amount of 0
        dp[0] = 0;
        
        // Compute the minimum coins for every amount up to the target
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        // If dp[amount] is still the initial placeholder value, it's impossible
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
