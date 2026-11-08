/*
 * Approach: Greedy single pass. At the first drop nums[i-1] > nums[i], fix it
 * by lowering nums[i-1] when that keeps it >= nums[i-2]; otherwise raise
 * nums[i] to nums[i-1]. A second drop means more than one change is needed.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int changes = 0;
        for (int i = 1; i < (int)nums.size(); ++i) {
            if (nums[i - 1] <= nums[i]) continue;
            if (++changes > 1) return false;
            if (i >= 2 && nums[i - 2] > nums[i]) nums[i] = nums[i - 1];
            else nums[i - 1] = nums[i];
        }
        return true;
    }
};
