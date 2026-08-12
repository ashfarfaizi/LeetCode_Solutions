#include <string>
#include <vector>

class Solution {
public:
    int numDecodings(std::string s) {
        if (s.empty() || s[0] == '0') {
            return 0;
        }
        
        int n = s.length();
        
        // Using space-optimized dynamic programming (storing only the last two states)
        // prev2 corresponds to dp[i-2], prev1 corresponds to dp[i-1]
        int prev2 = 1; // Base case for empty string matching double-digit decodes
        int prev1 = 1; // Base case for string of length 1 (already verified s[0] != '0')
        
        for (int i = 2; i <= n; ++i) {
            int current = 0;
            
            // Single digit check: Must not be '0'
            if (s[i - 1] != '0') {
                current += prev1;
            }
            
            // Double digit check: Must be between "10" and "26"
            int twoDigit = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            if (twoDigit >= 10 && twoDigit <= 26) {
                current += prev2;
            }
            
            // Slide state windows forward
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};
