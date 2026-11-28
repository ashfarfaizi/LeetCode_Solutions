/*
 * Approach: DP over words sorted by length. For each word, try deleting each
 * character; if the shorter word was seen, extend its chain.
 * Time: O(n log n + n * L^2)   Space: O(n * L)
 */
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(),
             [](const string& a, const string& b) { return a.size() < b.size(); });
        unordered_map<string, int> dp;
        int best = 0;
        for (const string& w : words) {
            int cur = 1;
            for (size_t i = 0; i < w.size(); i++) {
                string prev = w.substr(0, i) + w.substr(i + 1);
                auto it = dp.find(prev);
                if (it != dp.end()) cur = max(cur, it->second + 1);
            }
            dp[w] = cur;
            best = max(best, cur);
        }
        return best;
    }
};
