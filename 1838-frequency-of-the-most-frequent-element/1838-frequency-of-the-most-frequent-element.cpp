/*
 * Approach: Sort, then slide a window where every element is raised to the
 * window's right end nums[r]. The cost is nums[r] * len - sum(window); shrink
 * from the left while it exceeds k. The widest valid window is the answer.
 *
 * Time:  O(n log n)
 * Space: O(1) besides sorting
 */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        long long sum = 0;
        int best = 0;
        for (int l = 0, r = 0; r < (int)nums.size(); ++r) {
            sum += nums[r];
            while ((long long)nums[r] * (r - l + 1) - sum > k) sum -= nums[l++];
            best = max(best, r - l + 1);
        }
        return best;
    }
};
