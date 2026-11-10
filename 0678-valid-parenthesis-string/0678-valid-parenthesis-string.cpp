/*
 * Approach: Greedy range of open counts. Track the minimum and maximum number
 * of unmatched '(' possible so far, treating '*' as ')' for the minimum and
 * '(' for the maximum. If the maximum goes negative the string is invalid;
 * clamp the minimum at 0. Valid iff the minimum can reach 0 at the end.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    bool checkValidString(string s) {
        int lo = 0, hi = 0;
        for (char c : s) {
            if (c == '(') {
                ++lo;
                ++hi;
            } else if (c == ')') {
                --lo;
                --hi;
            } else {
                --lo;
                ++hi;
            }
            if (hi < 0) return false;
            lo = max(lo, 0);
        }
        return lo == 0;
    }
};
