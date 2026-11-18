/*
 * Approach: invert the question. Let dp[e] be the most floors that can be
 * resolved with e eggs and m moves. One drop either breaks (leaving e-1 eggs,
 * m-1 moves for the floors below) or survives (e eggs, m-1 moves for the
 * floors above), so dp_m[e] = dp_{m-1}[e-1] + dp_{m-1}[e] + 1. Increase m
 * until dp[k] >= n, updating e from high to low to reuse one array.
 *
 * Time:  O(k * log n) roughly (m grows logarithmically for k >= 2)
 * Space: O(k)
 */
class Solution {
public:
    int superEggDrop(int k, int n) {
        vector<long long> dp(k + 1, 0);
        int moves = 0;
        while (dp[k] < n) {
            ++moves;
            for (int e = k; e >= 1; --e) dp[e] = dp[e] + dp[e - 1] + 1;
        }
        return moves;
    }
};
