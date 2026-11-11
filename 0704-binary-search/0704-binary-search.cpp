/*
 * Approach: Classic binary search on the closed range [lo, hi], computing
 * the midpoint as lo + (hi - lo) / 2 to avoid overflow.
 * Time: O(log n), Space: O(1)
 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }
};
