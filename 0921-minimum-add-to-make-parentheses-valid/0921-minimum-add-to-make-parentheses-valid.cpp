/*
 * Approach: scan left to right tracking the number of unmatched '('. A ')'
 * closes one of them if any is open; otherwise it needs an inserted '('.
 * At the end every still-open '(' needs an inserted ')'.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0, inserts = 0;
        for (char c : s) {
            if (c == '(') {
                ++open;
            } else if (open > 0) {
                --open;
            } else {
                ++inserts;
            }
        }
        return inserts + open;
    }
};
