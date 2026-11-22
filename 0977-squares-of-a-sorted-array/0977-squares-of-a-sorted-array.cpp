/*
 * Approach: two pointers from both ends. The largest square always comes from
 * one of the two ends of the sorted input (the most negative or the most
 * positive value), so fill the result from the back, each time taking the
 * end with the larger absolute value and moving that pointer inward.
 *
 * Time:  O(n)
 * Space: O(1) extra besides the output
 */
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        int lo = 0, hi = n - 1;
        for (int pos = n - 1; pos >= 0; --pos) {
            if (abs(nums[lo]) > abs(nums[hi])) {
                result[pos] = nums[lo] * nums[lo];
                ++lo;
            } else {
                result[pos] = nums[hi] * nums[hi];
                --hi;
            }
        }
        return result;
    }
};
