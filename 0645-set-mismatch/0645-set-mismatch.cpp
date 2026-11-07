/*
 * Approach: Sign marking. For each value v, flip nums[|v| - 1] negative; if
 * it is already negative, v is the duplicate. Afterwards the one index still
 * positive gives the missing number.
 * Time: O(n), Space: O(1) extra (input is modified)
 */
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int duplicate = -1, missing = -1;
        for (int v : nums) {
            int idx = abs(v) - 1;
            if (nums[idx] < 0) duplicate = abs(v);
            else nums[idx] = -nums[idx];
        }
        for (int i = 0; i < (int)nums.size(); ++i)
            if (nums[i] > 0) missing = i + 1;
        return {duplicate, missing};
    }
};
