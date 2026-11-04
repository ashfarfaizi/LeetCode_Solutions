/*
 * Approach: DP over (stone, last jump). dp[i] holds the jump lengths that can
 * land on stone i. For every stone in order and every k in dp[i], try jumps
 * k-1, k, k+1; if a stone exists at that position (hash map lookup), add the
 * jump to its set. The answer is whether the last stone's set is non-empty.
 * A jump that lands on stone i is at most i, so each set has O(n) entries.
 * Time: O(n^2), Space: O(n^2)
 */
class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        if (n > 1 && stones[1] != 1) return false;
        unordered_map<int, int> index;
        for (int i = 0; i < n; ++i) index[stones[i]] = i;
        vector<unordered_set<int>> dp(n);
        dp[0].insert(0);
        for (int i = 0; i < n; ++i) {
            for (int k : dp[i]) {
                for (int step = k - 1; step <= k + 1; ++step) {
                    if (step <= 0) continue;
                    auto it = index.find(stones[i] + step);
                    if (it != index.end()) dp[it->second].insert(step);
                }
            }
        }
        return !dp[n - 1].empty();
    }
};
