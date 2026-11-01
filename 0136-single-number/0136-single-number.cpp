/*
 * Approach: XOR all values. Pairs cancel out (x ^ x = 0), leaving the
 * element that appears exactly once.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int x = 0;
        for (int v : nums) x ^= v;
        return x;
    }
};
