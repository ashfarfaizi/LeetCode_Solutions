#pragma GCC optimize ("O2")

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // If s is shorter than t, it's impossible to form t as a subsequence
        if (m < n) return 0;
        
        // dp[j] stores the number of distinct subsequences matching t[0...j-1]
        // Using unsigned int to prevent potential runtime overflows before truncation
        vector<unsigned int> dp(n + 1, 0);
        
        // Base case: An empty string t has exactly 1 matching subsequence (deleting all characters of s)
        dp[0] = 1;
        
        // Traverse through each character of s
        for (int i = 1; i <= m; ++i) {
            // Traverse backwards through t to use the values from the previous iteration loop
            for (int j = n; j >= 1; --j) {
                // If characters match, we can either:
                // 1. Match s[i-1] with t[j-1] -> add dp[j-1]
                // 2. Ignore s[i-1] -> keep dp[j]
                if (s[i-1] == t[j-1]) {
                    dp[j] += dp[j-1];
                }
            }
        }
        
        return dp[n];
    }
};
