/*
 * Approach: Sliding window. Since all values are positive, extend the right
 * end and shrink from the left while the product is >= k. Every window
 * [left, right] then contributes right - left + 1 subarrays ending at right.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        long long prod = 1;
        int count = 0, left = 0;
        for (int right = 0; right < (int)nums.size(); ++right) {
            prod *= nums[right];
            while (prod >= k) prod /= nums[left++];
            count += right - left + 1;
        }
        return count;
    }
};
