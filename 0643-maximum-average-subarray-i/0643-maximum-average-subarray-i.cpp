/*
 * Approach: Fixed-size sliding window. Sum the first k elements, then slide
 * the window one step at a time, adding the new element and dropping the old
 * one, keeping the largest sum. Divide once at the end.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        long long window = 0;
        for (int i = 0; i < k; ++i) window += nums[i];
        long long best = window;
        for (int i = k; i < (int)nums.size(); ++i) {
            window += nums[i] - nums[i - k];
            best = max(best, window);
        }
        return (double)best / k;
    }
};
