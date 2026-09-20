#include <vector>
#include <climits>

class Solution {
public:
    int combinationSum4(std::vector<int>& nums, int target) {
        // dp[i] will store the number of combinations that add up to i
        std::vector<int> dp(target + 1, 0);
        
        // Base case: 1 way to get a target of 0 (empty combination)
        dp[0] = 1;
        
        // Build up combinations for every value from 1 to target
        for (int i = 1; i <= target; ++i) {
            for (int num : nums) {
                if (i >= num) {
                    // Prevent integer overflow for test cases where intermediate combinations blow up
                    if (dp[i] <= INT_MAX - dp[i - num]) {
                        dp[i] += dp[i - num];
                    }
                }
            }
        }
        
        return dp[target];
    }
};
