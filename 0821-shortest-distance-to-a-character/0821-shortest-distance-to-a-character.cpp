/*
 * Approach: Two passes. Left to right records the distance to the most
 * recent occurrence of c; right to left takes the minimum with the distance
 * to the next occurrence. A sentinel far away handles the edges.
 * Time: O(n), Space: O(1) besides the output
 */
class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        int n = s.size();
        vector<int> ans(n);
        int last = -2 * n;
        for (int i = 0; i < n; ++i) {
            if (s[i] == c) last = i;
            ans[i] = i - last;
        }
        last = 3 * n;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == c) last = i;
            ans[i] = min(ans[i], last - i);
        }
        return ans;
    }
};
