/*
 * Approach: one pass tracking whether we have seen an increase and whether
 * we have seen a decrease; the array is monotonic unless both happened.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        bool inc = false, dec = false;
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1]) inc = true;
            if (nums[i] < nums[i - 1]) dec = true;
            if (inc && dec) return false;
        }
        return true;
    }
};
