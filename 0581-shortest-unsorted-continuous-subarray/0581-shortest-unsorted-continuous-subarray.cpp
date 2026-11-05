/*
 * Approach: Scan left to right tracking the running maximum; the last index
 * whose value is below that maximum is the right edge of the unsorted window.
 * Symmetrically, scan right to left with the running minimum for the left edge.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = -1;
        int mx = INT_MIN, mn = INT_MAX;
        for (int i = 0; i < n; ++i) {
            mx = max(mx, nums[i]);
            if (nums[i] < mx) right = i;
            mn = min(mn, nums[n - 1 - i]);
            if (nums[n - 1 - i] > mn) left = n - 1 - i;
        }
        return right - left + 1;
    }
};
