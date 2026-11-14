/*
 * Approach: One pass tracking the largest value (with its index) and the
 * second largest. The answer is valid iff largest >= 2 * second.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        int best = -1, second = -1, idx = -1;
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (nums[i] > best) {
                second = best;
                best = nums[i];
                idx = i;
            } else if (nums[i] > second) {
                second = nums[i];
            }
        }
        return best >= 2 * second ? idx : -1;
    }
};
