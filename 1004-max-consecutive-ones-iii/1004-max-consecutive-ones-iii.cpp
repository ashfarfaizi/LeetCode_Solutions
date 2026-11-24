/*
 * Approach: Sliding window that holds at most k zeros. Extend the right end
 * one step at a time; whenever the window contains more than k zeros, move
 * the left end forward until it is valid again. The widest valid window is
 * the answer.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0, zeros = 0, best = 0;
        for (int right = 0; right < (int)nums.size(); ++right) {
            if (nums[right] == 0) ++zeros;
            while (zeros > k) {
                if (nums[left] == 0) --zeros;
                ++left;
            }
            best = max(best, right - left + 1);
        }
        return best;
    }
};
