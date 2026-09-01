#include <vector>
#include <algorithm>

class Solution {
private:
    // Helper function to solve the linear House Robber I problem
    int robLinear(const std::vector<int>& nums, int start, int end) {
        int prev2 = 0; // Maximum loot if we skip the previous house
        int prev1 = 0; // Maximum loot if we consider the previous house
        
        for (int i = start; i <= end; ++i) {
            int current = std::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }

public:
    int rob(std::vector<int>& nums) {
        int n = nums.size();
        
        // Base cases
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        // Return the max of excluding the last house OR excluding the first house
        int robRange1 = robLinear(nums, 0, n - 2);
        int robRange2 = robLinear(nums, 1, n - 1);
        
        return std::max(robRange1, robRange2);
    }
};
