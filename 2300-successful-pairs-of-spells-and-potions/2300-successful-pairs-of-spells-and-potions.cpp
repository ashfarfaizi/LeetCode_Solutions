/*
 * Approach: sort the potions once. For a spell s we need potion >= ceil(success / s);
 * binary search for the first such potion and count everything after it.
 * Time: O((n + m) log m), Space: O(1) extra (besides the output)
 */
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        const int m = potions.size();
        vector<int> res;
        res.reserve(spells.size());
        for (long long s : spells) {
            long long need = (success + s - 1) / s;
            auto it = lower_bound(potions.begin(), potions.end(), need,
                                  [](int p, long long v) { return p < v; });
            res.push_back(m - int(it - potions.begin()));
        }
        return res;
    }
};
