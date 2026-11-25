/*
 * Approach: Swapping positions means order is irrelevant; relabelling
 * letters means only the multiset of frequencies matters, but no new letter
 * can appear. So the strings are close iff they use the same set of letters
 * and their sorted frequency lists are equal.
 *
 * Time:  O(n) (sorting 26 counts is constant)
 * Space: O(1)
 */
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if (word1.size() != word2.size()) return false;
        array<int, 26> a{}, b{};
        for (char c : word1) ++a[c - 'a'];
        for (char c : word2) ++b[c - 'a'];
        for (int i = 0; i < 26; ++i) {
            if ((a[i] == 0) != (b[i] == 0)) return false;
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return a == b;
    }
};
