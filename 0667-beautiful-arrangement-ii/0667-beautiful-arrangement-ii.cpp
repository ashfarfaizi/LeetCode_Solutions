/*
 * Approach: Construction. Emit 1..n-k-1 in order (all gaps 1), then zig-zag
 * over the window [n-k, n]: n-k, n, n-k+1, n-1, ... which produces the gaps
 * k, k-1, ..., 1. Together that is exactly k distinct differences.
 * Time: O(n), Space: O(1) besides the output
 */
class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        res.reserve(n);
        for (int i = 1; i < n - k; ++i) res.push_back(i);
        int lo = n - k, hi = n;
        bool takeLow = true;
        while (lo <= hi) {
            res.push_back(takeLow ? lo++ : hi--);
            takeLow = !takeLow;
        }
        return res;
    }
};
