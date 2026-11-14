/*
 * Approach: Iterative expansion. Start with the original string; for each
 * letter position, duplicate every string built so far with that character's
 * case flipped. Digits leave the list unchanged.
 * Time: O(n * 2^L), Space: O(n * 2^L) for the output (L = number of letters)
 */
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> res{s};
        for (int i = 0; i < (int)s.size(); ++i) {
            if (!isalpha(static_cast<unsigned char>(s[i]))) continue;
            int sz = res.size();
            for (int j = 0; j < sz; ++j) {
                string t = res[j];
                t[i] ^= 32;  // toggle ASCII case
                res.push_back(move(t));
            }
        }
        return res;
    }
};
