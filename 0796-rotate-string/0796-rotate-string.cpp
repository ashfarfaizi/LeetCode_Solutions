/*
 * Approach: Every rotation of s is a substring of s + s, so goal is a
 * rotation exactly when the lengths match and goal occurs in s + s.
 * Time: O(n^2) worst case with std::string::find, Space: O(n)
 */
class Solution {
public:
    bool rotateString(string s, string goal) {
        return s.size() == goal.size() && (s + s).find(goal) != string::npos;
    }
};
