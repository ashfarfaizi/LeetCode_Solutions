/*
 * Approach: binary search on the eating speed k in [1, max(piles)]. The
 * hours needed, sum of ceil(pile / k), only decreases as k grows, so find
 * the smallest k whose total fits within h hours.
 *
 * Time:  O(n log M), M = largest pile
 * Space: O(1)
 */
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1, hi = *max_element(piles.begin(), piles.end());
        while (lo < hi) {
            int k = lo + (hi - lo) / 2;
            long long hours = 0;
            for (int p : piles) hours += (p + k - 1) / k;
            if (hours <= h) {
                hi = k;
            } else {
                lo = k + 1;
            }
        }
        return lo;
    }
};
