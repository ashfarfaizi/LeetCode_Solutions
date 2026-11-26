/*
 * Approach: running prefix sum of the gains, tracking the maximum seen
 * (starting from the initial altitude 0).
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int cur = 0, best = 0;
        for (int g : gain) {
            cur += g;
            best = max(best, cur);
        }
        return best;
    }
};
