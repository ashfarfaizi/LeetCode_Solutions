/*
 * Approach: Backtracking into k buckets. Sort descending so large numbers
 * fail fast, place each number into a bucket that stays within the target,
 * and skip buckets with the same current sum as one already tried (which
 * also covers trying more than one empty bucket).
 * Time: O(k^n) worst case, heavily pruned; Space: O(n + k)
 */
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) return false;
        target = total / k;
        sort(nums.rbegin(), nums.rend());
        if (nums[0] > target) return false;
        buckets.assign(k, 0);
        return place(nums, 0);
    }

private:
    int target = 0;
    vector<int> buckets;

    bool place(const vector<int>& nums, size_t i) {
        if (i == nums.size()) return true;
        for (size_t b = 0; b < buckets.size(); ++b) {
            if (buckets[b] + nums[i] > target) continue;
            bool seen = false;
            for (size_t p = 0; p < b && !seen; ++p) seen = buckets[p] == buckets[b];
            if (seen) continue;
            buckets[b] += nums[i];
            if (place(nums, i + 1)) return true;
            buckets[b] -= nums[i];
        }
        return false;
    }
};
