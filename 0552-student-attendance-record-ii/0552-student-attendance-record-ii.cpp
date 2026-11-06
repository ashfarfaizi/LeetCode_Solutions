/*
 * Approach: DP over the record length with state (absences used: 0/1,
 * trailing consecutive lates: 0/1/2). Each day append 'P' (reset lates),
 * 'A' (if no absence yet; reset lates) or 'L' (if fewer than 2 trailing).
 * Only the previous day's 6 states are needed.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int checkRecord(int n) {
        const long long MOD = 1'000'000'007;
        long long dp[2][3] = {{1, 0, 0}, {0, 0, 0}};  // empty record
        for (int day = 0; day < n; ++day) {
            long long next[2][3] = {};
            for (int a = 0; a < 2; ++a) {
                for (int l = 0; l < 3; ++l) {
                    long long cur = dp[a][l];
                    if (!cur) continue;
                    next[a][0] = (next[a][0] + cur) % MOD;                      // 'P'
                    if (a == 0) next[1][0] = (next[1][0] + cur) % MOD;          // 'A'
                    if (l < 2) next[a][l + 1] = (next[a][l + 1] + cur) % MOD;   // 'L'
                }
            }
            memcpy(dp, next, sizeof(dp));
        }
        long long total = 0;
        for (auto& row : dp)
            for (long long v : row) total = (total + v) % MOD;
        return static_cast<int>(total);
    }
};
