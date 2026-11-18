/*
 * Approach: count every word from both sentences in one hash map; a word is
 * uncommon exactly when its combined count is 1.
 *
 * Time:  O(n + m) over the sentence lengths
 * Space: O(n + m)
 */
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, int> count;
        istringstream in(s1 + " " + s2);
        string w;
        while (in >> w) ++count[w];
        vector<string> res;
        for (auto& [word, c] : count)
            if (c == 1) res.push_back(word);
        return res;
    }
};
