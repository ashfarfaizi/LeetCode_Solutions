/*
 * Approach: sort jobs by end time. dp[i] is the best profit using the first i
 * jobs; for job i either skip it (dp[i]) or take it and add the best profit
 * among jobs ending at or before its start, found by binary search.
 * Time: O(n log n), Space: O(n)
 */
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int x, int y) { return endTime[x] < endTime[y]; });
        vector<int> ends(n);
        for (int i = 0; i < n; ++i) ends[i] = endTime[idx[i]];
        vector<int> dp(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int j = idx[i];
            int k = upper_bound(ends.begin(), ends.begin() + i, startTime[j]) - ends.begin();
            dp[i + 1] = max(dp[i], dp[k] + profit[j]);
        }
        return dp[n];
    }
};
