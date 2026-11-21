/*
 * Approach: bottom-up merge sort. Merge runs of width 1, 2, 4, ... from the
 * array into a buffer and swap the two each pass, so no recursion is needed
 * and the worst case stays O(n log n) regardless of input order.
 *
 * Time:  O(n log n)
 * Space: O(n)
 */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> src = nums, dst(n);
        for (int width = 1; width < n; width *= 2) {
            for (int lo = 0; lo < n; lo += 2 * width) {
                int mid = min(lo + width, n), hi = min(lo + 2 * width, n);
                int i = lo, j = mid, k = lo;
                while (i < mid && j < hi) dst[k++] = src[j] < src[i] ? src[j++] : src[i++];
                while (i < mid) dst[k++] = src[i++];
                while (j < hi) dst[k++] = src[j++];
            }
            swap(src, dst);
        }
        return src;
    }
};
