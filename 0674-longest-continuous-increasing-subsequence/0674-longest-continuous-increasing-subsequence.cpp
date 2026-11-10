/*
 * Approach: Single pass. Extend the current run while each element is larger
 * than the previous one, reset it to 1 otherwise, and keep the longest run.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int best = 1, run = 1;
        for (int i = 1; i < (int)nums.size(); ++i) {
            run = nums[i] > nums[i - 1] ? run + 1 : 1;
            best = max(best, run);
        }
        return best;
    }
};
