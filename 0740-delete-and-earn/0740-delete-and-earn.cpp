/*
 * Approach: Bucket the total points per value. Taking value v forbids v-1 and
 * v+1, which is exactly the House Robber recurrence over the value axis:
 * best(v) = max(best(v-1), best(v-2) + total[v]).
 * Time: O(n + M), Space: O(M) where M is the maximum value
 */
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxVal = *max_element(nums.begin(), nums.end());
        vector<int> total(maxVal + 1, 0);
        for (int x : nums) total[x] += x;

        int take = 0, skip = 0;  // best ending with v taken / not taken
        for (int v = 0; v <= maxVal; ++v) {
            int newTake = skip + total[v];
            skip = max(skip, take);
            take = newTake;
        }
        return max(take, skip);
    }
};
