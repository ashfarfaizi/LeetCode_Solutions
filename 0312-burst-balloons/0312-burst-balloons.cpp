#include <vector>
#include <algorithm>

class Solution {
public:
    int maxCoins(std::vector<int>& nums) {
        // Pad the original array with 1 at both ends
        std::vector<int> A;
        A.push_back(1);
        for (int x : nums) {
            A.push_back(x);
        }
        A.push_back(1);
        
        int n = A.size();
        // dp[i][j] will store the max coins collected by bursting all balloons between i and j
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        
        // len is the length of the interval between i and j
        for (int len = 2; len < n; ++len) {
            for (int i = 0; i < n - len; ++i) {
                int j = i + len;
                
                // Iterate through all possible choices for the last balloon 'k' to burst in (i, j)
                for (int k = i + 1; k < j; ++k) {
                    int current_coins = dp[i][k] + dp[k][j] + A[i] * A[k] * A[j];
                    dp[i][j] = std::max(dp[i][j], current_coins);
                }
            }
        }
        
        // The answer is the maximum coins for the full range between the padded boundaries
        return dp[0][n - 1];
    }
};
