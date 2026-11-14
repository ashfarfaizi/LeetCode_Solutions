/*
 * Approach: Count the plate's letters (lower-cased), then for each word build
 * its letter counts and check that they dominate the plate's. Keep the first
 * shortest word that qualifies.
 * Time: O(P + sum of word lengths), Space: O(1) (26-letter tables)
 */
class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        array<int, 26> need{};
        for (char c : licensePlate)
            if (isalpha(static_cast<unsigned char>(c)))
                ++need[tolower(static_cast<unsigned char>(c)) - 'a'];

        string best;
        bool found = false;
        for (const string& w : words) {
            if (found && w.size() >= best.size()) continue;
            array<int, 26> have{};
            for (char c : w) ++have[c - 'a'];
            bool ok = true;
            for (int i = 0; i < 26 && ok; ++i) ok = have[i] >= need[i];
            if (ok) {
                best = w;
                found = true;
            }
        }
        return best;
    }
};
