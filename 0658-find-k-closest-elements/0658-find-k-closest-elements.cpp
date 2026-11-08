/*
 * Approach: Binary search on the window start. The answer is a contiguous
 * window arr[lo..lo+k-1]. For a candidate start mid, if x is farther from
 * arr[mid] than from arr[mid+k], the window should shift right; otherwise it
 * should stay or shift left.
 * Time: O(log(n - k) + k), Space: O(1) besides the output
 */
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int lo = 0, hi = (int)arr.size() - k;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (x - arr[mid] > arr[mid + k] - x) lo = mid + 1;
            else hi = mid;
        }
        return vector<int>(arr.begin() + lo, arr.begin() + lo + k);
    }
};
