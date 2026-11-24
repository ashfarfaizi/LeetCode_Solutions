/*
 * Approach: Use the result string as a stack. Letters are pushed; a star
 * pops the most recent letter.
 *
 * Time:  O(n)
 * Space: O(n) for the result
 */
class Solution {
public:
    string removeStars(string s) {
        string out;
        out.reserve(s.size());
        for (char c : s) {
            if (c == '*') out.pop_back();
            else out.push_back(c);
        }
        return out;
    }
};
