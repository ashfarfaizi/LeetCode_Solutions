/*
 * Approach: Build each word's Morse transformation from the fixed letter
 * table and insert it into a hash set; the set size is the answer.
 * Time: O(total characters), Space: O(total characters)
 */
class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        static const string code[26] = {
            ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
            "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
            "..-", "...-", ".--", "-..-", "-.--", "--.."};
        unordered_set<string> seen;
        for (const string& w : words) {
            string t;
            for (char c : w) t += code[c - 'a'];
            seen.insert(t);
        }
        return seen.size();
    }
};
