class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        vector<int> dp(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            vector<int> next_dp(n, 0);
            next_dp[i] = 1;
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    next_dp[j] = dp[j - 1] + 2;
                } else {
                    next_dp[j] = max(dp[j], next_dp[j - 1]);
                }
            }
            dp = move(next_dp);
        }
        return dp[n - 1];
    }
};
