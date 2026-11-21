/*
 * Approach: a circular maximum subarray either does not wrap (plain Kadane
 * maximum) or wraps, in which case it is the total minus a minimum subarray
 * in the middle. Run Kadane for both the max and the min in one pass; if every
 * element is negative the wrapping case would pick an empty array, so return
 * the plain maximum then.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int total = 0, curMax = 0, curMin = 0;
        int best = nums[0], worst = nums[0];
        for (int x : nums) {
            curMax = max(curMax + x, x);
            curMin = min(curMin + x, x);
            best = max(best, curMax);
            worst = min(worst, curMin);
            total += x;
        }
        return best < 0 ? best : max(best, total - worst);
    }
};
