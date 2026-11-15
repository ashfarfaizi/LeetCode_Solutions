/*
 * Approach: Count the letters of s, emit each letter of order as many times
 * as it occurs, then append whatever letters remain.
 * Time: O(|order| + |s|), Space: O(1) besides the output
 */
class Solution {
public:
    string customSortString(string order, string s) {
        int cnt[26] = {};
        for (char c : s) ++cnt[c - 'a'];
        string res;
        res.reserve(s.size());
        for (char c : order) {
            res.append(cnt[c - 'a'], c);
            cnt[c - 'a'] = 0;
        }
        for (int i = 0; i < 26; ++i) res.append(cnt[i], char('a' + i));
        return res;
    }
};
