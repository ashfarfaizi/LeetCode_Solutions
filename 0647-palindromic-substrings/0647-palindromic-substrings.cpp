/*
 * Approach: Expand around every possible centre - each character (odd length)
 * and each gap between characters (even length) - counting one palindrome per
 * successful expansion step.
 * Time: O(n^2), Space: O(1)
 */
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size(), total = 0;
        for (int c = 0; c < 2 * n - 1; ++c) {
            int l = c / 2, r = l + c % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {
                ++total;
                --l;
                ++r;
            }
        }
        return total;
    }
};
