/*
 * Approach: walk both strings from the end with two pointers. Each pointer
 * keeps a count of pending backspaces and skips characters they delete, so
 * we only ever compare characters that survive. No extra strings are built.
 *
 * Time:  O(n + m)
 * Space: O(1)
 */
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int i = (int)s.size() - 1, j = (int)t.size() - 1;
        while (i >= 0 || j >= 0) {
            i = nextValid(s, i);
            j = nextValid(t, j);
            if (i < 0 || j < 0) return i < 0 && j < 0;
            if (s[i] != t[j]) return false;
            --i;
            --j;
        }
        return true;
    }

private:
    // Index of the next surviving character at or before i, or -1.
    int nextValid(const string& str, int i) {
        int skip = 0;
        while (i >= 0) {
            if (str[i] == '#') {
                ++skip;
            } else if (skip > 0) {
                --skip;
            } else {
                break;
            }
            --i;
        }
        return i;
    }
};
