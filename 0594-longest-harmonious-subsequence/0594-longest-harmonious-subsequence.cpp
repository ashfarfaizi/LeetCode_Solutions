/*
 * Approach: Hash map counting. A harmonious subsequence uses only two values
 * x and x + 1, so count every value and, for each x whose x + 1 also appears,
 * the candidate length is count[x] + count[x + 1].
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> count;
        for (int x : nums) ++count[x];
        int best = 0;
        for (auto& [x, c] : count) {
            auto it = count.find(x + 1);
            if (it != count.end()) best = max(best, c + it->second);
        }
        return best;
    }
};
