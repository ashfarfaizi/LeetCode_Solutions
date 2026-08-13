#include <string>
#include <vector>

class Solution {
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        int m = s1.length();
        int n = s2.length();
        
        // If the total length of s1 and s2 doesn't match s3, it's impossible to interleave
        if (m + n != s3.length()) {
            return false;
        }
        
        // Optimization: Ensure the DP array size is min(m, n) to consume minimal space.
        // If s1 is shorter than s2, swap them so that the DP vector size relies on s2 (the shorter one).
        if (m < n) {
            return isInterleave(s2, s1, s3);
        }
        
        // dp[j] will store whether s3[0...i+j-1] can be formed by interleaving s1[0...i-1] and s2[0...j-1]
        std::vector<bool> dp(n + 1, false);
        
        // Base Case: Empty s1 and empty s2 form an empty s3
        dp[0] = true;
        
        // Initialize the 0-th row (matching s2 elements when s1 is empty)
        for (int j = 1; j <= n; ++j) {
            dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
        }
        
        // Fill the DP table row by row
        for (int i = 1; i <= m; ++i) {
            // Update the first element of the row (matching s1 elements when s2 is empty)
            dp[0] = dp[0] && (s1[i - 1] == s3[i - 1]);
            
            for (int j = 1; j <= n; ++j) {
                // To form s3[i+j-1], we can either:
                // 1. Take the current character from s1 (s1[i-1]) if s1[i-1] == s3[i+j-1] and previous match was valid (dp[j])
                // 2. Take the current character from s2 (s2[j-1]) if s2[j-1] == s3[i+j-1] and previous match was valid (dp[j-1])
                dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) || 
                        (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        
        return dp[n];
    }
};
