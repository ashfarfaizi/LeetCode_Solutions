/*
 * Approach: The characters we keep form a common subsequence, so keep the
 * longest one. Compute the LCS length with a rolling 1-D DP and delete
 * everything else from both words: m + n - 2 * LCS.
 * Time: O(m*n), Space: O(n)
 */
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            int diag = 0;  // dp[i-1][j-1]
            for (int j = 1; j <= n; ++j) {
                int up = dp[j];
                dp[j] = word1[i - 1] == word2[j - 1] ? diag + 1 : max(dp[j], dp[j - 1]);
                diag = up;
            }
        }
        return m + n - 2 * dp[n];
    }
};
