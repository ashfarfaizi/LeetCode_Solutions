/*
 * Approach: If the most frequent letter appears more than (n + 1) / 2 times it
 * is impossible. Otherwise fill the even indices first, starting with the most
 * frequent letter, then wrap around to the odd indices with the rest; equal
 * letters always end up at least two positions apart.
 * Time: O(n), Space: O(1) extra beyond the output
 */
class Solution {
public:
    string reorganizeString(string s) {
        int n = s.size();
        array<int, 26> cnt{};
        for (char c : s) ++cnt[c - 'a'];

        int top = max_element(cnt.begin(), cnt.end()) - cnt.begin();
        if (cnt[top] > (n + 1) / 2) return "";

        string res(n, ' ');
        int pos = 0;
        auto place = [&](int letter) {
            while (cnt[letter] > 0) {
                if (pos >= n) pos = 1;
                res[pos] = 'a' + letter;
                pos += 2;
                --cnt[letter];
            }
        };
        place(top);
        for (int c = 0; c < 26; ++c) place(c);
        return res;
    }
};
