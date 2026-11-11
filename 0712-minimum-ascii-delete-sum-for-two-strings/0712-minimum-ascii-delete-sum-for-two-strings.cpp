/*
 * Approach: DP like edit distance with only deletions. dp[i][j] is the
 * minimum ASCII cost to make s1[i..] and s2[j..] equal. If the heads match
 * keep both; otherwise delete one head and pay its ASCII value. A rolling
 * 1-D array is enough.
 * Time: O(m * n), Space: O(n)
 */
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<int> dp(n + 1, 0);
        for (int j = n - 1; j >= 0; --j) dp[j] = dp[j + 1] + s2[j];
        for (int i = m - 1; i >= 0; --i) {
            int diag = dp[n];
            dp[n] += s1[i];
            for (int j = n - 1; j >= 0; --j) {
                int below = dp[j];
                if (s1[i] == s2[j]) dp[j] = diag;
                else dp[j] = min(s1[i] + below, s2[j] + dp[j + 1]);
                diag = below;
            }
        }
        return dp[0];
    }
};
