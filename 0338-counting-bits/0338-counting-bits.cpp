/*
 * Approach: DP on the binary representation. i >> 1 drops the lowest bit,
 * so bits[i] = bits[i >> 1] + (i & 1), and i >> 1 is always computed first.
 * Time: O(n), Space: O(1) besides the output
 */
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> bits(n + 1, 0);
        for (int i = 1; i <= n; ++i) bits[i] = bits[i >> 1] + (i & 1);
        return bits;
    }
};
