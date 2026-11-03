/*
 * Approach: Single scan with a running streak counter that resets on 0;
 * track the largest streak seen.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int best = 0, cur = 0;
        for (int x : nums) {
            cur = x == 1 ? cur + 1 : 0;
            best = max(best, cur);
        }
        return best;
    }
};
