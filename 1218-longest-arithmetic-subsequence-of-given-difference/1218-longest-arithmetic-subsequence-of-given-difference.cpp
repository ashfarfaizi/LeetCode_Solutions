/*
 * Approach: DP keyed by value. best[v] is the longest valid subsequence
 * ending with value v seen so far; when x arrives it extends the chain
 * ending at x - difference: best[x] = best[x - difference] + 1.
 *
 * Time:  O(n) expected
 * Space: O(n)
 */
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        unordered_map<int, int> best;
        int ans = 0;
        for (int x : arr) {
            auto it = best.find(x - difference);
            int len = (it == best.end() ? 0 : it->second) + 1;
            best[x] = len;
            ans = max(ans, len);
        }
        return ans;
    }
};
