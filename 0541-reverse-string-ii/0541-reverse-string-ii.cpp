/*
 * Approach: Step i through the string by 2k and reverse the range
 * [i, min(i + k, n)) in place.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for (int i = 0; i < n; i += 2 * k)
            reverse(s.begin() + i, s.begin() + min(i + k, n));
        return s;
    }
};
