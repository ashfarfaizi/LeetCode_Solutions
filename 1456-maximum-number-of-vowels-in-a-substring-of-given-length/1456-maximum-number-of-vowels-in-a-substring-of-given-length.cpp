/*
 * Approach: fixed-size sliding window. Add the incoming character's vowel
 * flag and subtract the outgoing one, tracking the best window count.
 * Time: O(n), Space: O(1)
 */
class Solution {
    static bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
public:
    int maxVowels(string s, int k) {
        int cur = 0, best = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            cur += isVowel(s[i]);
            if (i >= k) cur -= isVowel(s[i - k]);
            best = max(best, cur);
        }
        return best;
    }
};
