/*
 * Approach: Greedy with two counters. count[v] is how many copies of v are
 * still unused and tails[v] is how many runs currently end at v - 1 and want
 * v next. Each number first extends an existing run; if none wants it, it must
 * start a new run using v + 1 and v + 2, otherwise the split is impossible.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int, int> count, tails;
        for (int v : nums) ++count[v];
        for (int v : nums) {
            if (count[v] == 0) continue;
            --count[v];
            if (tails[v] > 0) {
                --tails[v];
                ++tails[v + 1];
            } else if (count[v + 1] > 0 && count[v + 2] > 0) {
                --count[v + 1];
                --count[v + 2];
                ++tails[v + 3];
            } else {
                return false;
            }
        }
        return true;
    }
};
