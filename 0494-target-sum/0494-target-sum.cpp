#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        
        // Edge cases based on mathematical formulation
        if (abs(target) > total_sum) return 0;
        if ((target + total_sum) % 2 != 0) return 0;
        
        int subset_target = (target + total_sum) / 2;
        
        // dp[i] stores the number of ways to reach a sum equal to i
        vector<int> dp(subset_target + 1, 0);
        dp[0] = 1; // Base case: 1 way to make a sum of 0 (empty subset)
        
        for (int num : nums) {
            // Traversed in reverse order to ensure we use each element only once (0/1 Knapsack rule)
            for (int j = subset_target; j >= num; --j) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[subset_target];
    }
};
