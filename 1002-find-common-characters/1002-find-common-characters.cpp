/*
 * Approach: keep a running minimum frequency per letter across all words;
 * emit each letter that many times at the end.
 * Time: O(total characters)   Space: O(26)
 */
class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        array<int, 26> common;
        common.fill(INT_MAX);
        for (const string& w : words) {
            array<int, 26> cnt{};
            for (char c : w) cnt[c - 'a']++;
            for (int i = 0; i < 26; i++) common[i] = min(common[i], cnt[i]);
        }
        vector<string> ans;
        for (int i = 0; i < 26; i++)
            for (int k = 0; k < common[i]; k++) ans.push_back(string(1, 'a' + i));
        return ans;
    }
};
