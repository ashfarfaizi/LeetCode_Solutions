/*
 * Approach: Sort the values. dp[x] counts trees rooted at x: 1 for the leaf,
 * plus dp[a] * dp[x / a] for every smaller a that divides x with x / a also
 * present (ordered pairs, so left/right swaps are counted separately).
 * Time: O(n^2), Space: O(n)
 */
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        const long long MOD = 1'000'000'007;
        sort(arr.begin(), arr.end());
        unordered_map<int, long long> dp;
        long long total = 0;
        for (int i = 0; i < (int)arr.size(); ++i) {
            long long ways = 1;
            for (int j = 0; j < i; ++j) {
                if (arr[i] % arr[j] != 0) continue;
                auto it = dp.find(arr[i] / arr[j]);
                if (it != dp.end()) ways = (ways + dp[arr[j]] * it->second) % MOD;
            }
            dp[arr[i]] = ways;
            total = (total + ways) % MOD;
        }
        return (int)total;
    }
};
