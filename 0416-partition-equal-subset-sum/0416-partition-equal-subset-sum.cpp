#include <vector>
#include <numeric>

class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        
        // If the total sum is odd, we cannot split it into two equal integer subsets
        if (totalSum % 2 != 0) {
            return false;
        }
        
        int target = totalSum / 2;
        std::vector<bool> dp(target + 1, false);
        dp[0] = true; // Base case: A sum of 0 is always possible
        
        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
            // Optimization: Stop early if we hit the target
            if (dp[target]) {
                return true;
            }
        }
        
        return dp[target];
    }
};
