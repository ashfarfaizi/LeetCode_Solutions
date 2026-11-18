/*
 * Approach: a word matches when the letter mapping is a bijection. Keep two
 * arrays, word->pattern and pattern->word, and reject on any conflict.
 *
 * Time:  O(total characters)
 * Space: O(1) per word (two 26-entry tables)
 */
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;
        for (const string& w : words)
            if (matches(w, pattern)) res.push_back(w);
        return res;
    }

private:
    static bool matches(const string& w, const string& p) {
        if (w.size() != p.size()) return false;
        array<char, 26> fwd{}, back{};
        for (size_t i = 0; i < w.size(); ++i) {
            char a = w[i], b = p[i];
            char& f = fwd[a - 'a'];
            char& r = back[b - 'a'];
            if (!f && !r) {
                f = b;
                r = a;
            } else if (f != b || r != a) {
                return false;
            }
        }
        return true;
    }
};
