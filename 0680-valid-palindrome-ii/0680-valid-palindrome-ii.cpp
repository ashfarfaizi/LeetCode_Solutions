/*
 * Approach: Two pointers. Move inward while the ends match. At the first
 * mismatch, the only options are deleting the left or the right character,
 * so check whether either remaining range is a palindrome.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    bool validPalindrome(string s) {
        int i = 0, j = (int)s.size() - 1;
        while (i < j) {
            if (s[i] != s[j]) return isPal(s, i + 1, j) || isPal(s, i, j - 1);
            ++i;
            --j;
        }
        return true;
    }

private:
    bool isPal(const string& s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }
};
