/*
 * Approach: DP over prefixes. dp[i] is the best sum for the first i
 * elements. For the last piece ending at i, try every length len in 1..k,
 * tracking the running maximum of that piece:
 * dp[i] = max(dp[i - len] + maxOfPiece * len).
 *
 * Time:  O(n * k)
 * Space: O(n)
 */
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int curMax = 0;
            for (int len = 1; len <= k && len <= i; ++len) {
                curMax = max(curMax, arr[i - len]);
                dp[i] = max(dp[i], dp[i - len] + curMax * len);
            }
        }
        return dp[n];
    }
};
