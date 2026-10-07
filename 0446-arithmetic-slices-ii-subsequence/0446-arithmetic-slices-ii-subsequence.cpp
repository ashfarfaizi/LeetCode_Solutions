#include <vector>
#include <unordered_map>

class Solution {
public:
    int numberOfArithmeticSlices(std::vector<int>& nums) {
        int n = nums.size();
        int total_count = 0;
        
        // dp[i][diff] stores the number of arithmetic subsequences ending at index i with a common difference of 'diff'
        std::vector<std::unordered_map<long long, int>> dp(n);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                // Prevent integer underflow/overflow during subtraction
                long long diff = (long long)nums[i] - nums[j];
                
                // Get the number of valid sequences ending at index j with difference 'diff'
                int count_at_j = dp[j].count(diff) ? dp[j][diff] : 0;
                
                // Any sequence ending at j can be extended to i, forming a sequence of length >= 3
                total_count += count_at_j;
                
                // Update dp[i][diff]: 
                // Add the extended sequences (count_at_j) + 1 for the new pair (nums[j], nums[i])
                dp[i][diff] += count_at_j + 1;
            }
        }
        
        return total_count;
    }
};
