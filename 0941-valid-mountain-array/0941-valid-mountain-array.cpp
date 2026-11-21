/*
 * Approach: walk up while values strictly increase, then down while they
 * strictly decrease. The array is a mountain only if the peak is neither the
 * first nor the last element and the descent reaches the end.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        int n = arr.size(), i = 0;
        while (i + 1 < n && arr[i] < arr[i + 1]) ++i;
        if (i == 0 || i == n - 1) return false;
        while (i + 1 < n && arr[i] > arr[i + 1]) ++i;
        return i == n - 1;
    }
};
