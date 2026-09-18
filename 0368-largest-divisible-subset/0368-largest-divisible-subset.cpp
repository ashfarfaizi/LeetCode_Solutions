#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
        if (nums.empty()) return {};
        
        // 1. Sort the input array
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        
        std::vector<int> dp(n, 1);
        std::vector<int> parent(n, -1);
        
        int max_size = 1;
        int max_idx = 0;
        
        // 2. Compute DP states
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
            // Track global maximum subset size and its ending index
            if (dp[i] > max_size) {
                max_size = dp[i];
                max_idx = i;
            }
        }
        
        // 3. Reconstruct the subset using the parent pointers
        std::vector<int> result;
        while (max_idx != -1) {
            result.push_back(nums[max_idx]);
            max_idx = parent[max_idx];
        }
        
        return result;
    }
};
