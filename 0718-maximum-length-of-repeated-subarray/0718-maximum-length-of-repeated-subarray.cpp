/*
 * Approach: DP on suffix matches. dp[j] holds the length of the common run
 * ending at nums1[i-1] and nums2[j-1]; iterate j backwards so one row is
 * enough. Track the maximum seen.
 * Time: O(n * m), Space: O(m)
 */
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums2.size(), best = 0;
        vector<int> dp(m + 1, 0);
        for (int i = 1; i <= (int)nums1.size(); ++i) {
            for (int j = m; j >= 1; --j) {
                dp[j] = nums1[i - 1] == nums2[j - 1] ? dp[j - 1] + 1 : 0;
                best = max(best, dp[j]);
            }
        }
        return best;
    }
};
