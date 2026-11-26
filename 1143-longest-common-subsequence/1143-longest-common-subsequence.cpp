/*
 * Approach: classic 2-D DP compressed to one row. dp[j] holds the LCS length
 * of text1[0..i) and text2[0..j). When characters match we extend the
 * diagonal value, otherwise take the best of dropping one character.
 * Time: O(m * n), Space: O(n)
 */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text2.size();
        vector<int> dp(n + 1, 0);
        for (char c : text1) {
            int diag = 0;  // dp[i-1][j-1]
            for (int j = 1; j <= n; ++j) {
                int up = dp[j];
                dp[j] = (c == text2[j - 1]) ? diag + 1 : max(dp[j], dp[j - 1]);
                diag = up;
            }
        }
        return dp[n];
    }
};
