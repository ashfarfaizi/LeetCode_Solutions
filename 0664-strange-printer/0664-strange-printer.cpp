/*
 * Approach: Interval DP. dp[i][j] is the fewest turns for s[i..j]. By default
 * s[i] is printed on its own: 1 + dp[i+1][j]. If some s[k] (i < k <= j)
 * equals s[i], the turn that prints s[i] can extend through s[k], giving
 * dp[i+1][k-1] + dp[k][j]. Take the minimum over all such k.
 * Time: O(n^3), Space: O(n^2)
 */
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; ++j) {
                dp[i][j] = 1 + dp[i + 1][j];
                for (int k = i + 1; k <= j; ++k) {
                    if (s[k] == s[i]) {
                        dp[i][j] = min(dp[i][j], dp[i + 1][k - 1] + dp[k][j]);
                    }
                }
            }
        }
        return n == 0 ? 0 : dp[0][n - 1];
    }
};
