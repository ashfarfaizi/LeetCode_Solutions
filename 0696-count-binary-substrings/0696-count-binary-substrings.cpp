/*
 * Approach: Group consecutive equal characters into run lengths. Each pair
 * of adjacent runs contributes min(prev, cur) valid substrings, because a
 * valid substring is k chars from the end of one run plus k from the next.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int countBinarySubstrings(string s) {
        int prev = 0, cur = 1, total = 0;
        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i] == s[i - 1]) {
                ++cur;
            } else {
                total += min(prev, cur);
                prev = cur;
                cur = 1;
            }
        }
        return total + min(prev, cur);
    }
};
