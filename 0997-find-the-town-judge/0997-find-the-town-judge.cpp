/*
 * Approach: Track a single score per person: +1 for each person who trusts
 * them, -1 for each person they trust. The judge is the unique person whose
 * score is exactly n - 1 (trusted by all others, trusts nobody).
 *
 * Time:  O(n + t) where t = trust.size()
 * Space: O(n)
 */
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> score(n + 1, 0);
        for (const auto& t : trust) {
            --score[t[0]];
            ++score[t[1]];
        }
        for (int i = 1; i <= n; ++i)
            if (score[i] == n - 1) return i;
        return -1;
    }
};
