/*
 * Approach: nums is a permutation, so following i -> nums[i] splits the
 * indices into disjoint cycles. Walk each unvisited cycle once, marking
 * visited elements in place (set to -1), and keep the longest cycle length.
 * Time: O(n), Space: O(1) extra (input is modified)
 */
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int best = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int len = 0;
            for (int j = i; nums[j] != -1; ++len) {
                int next = nums[j];
                nums[j] = -1;
                j = next;
            }
            best = max(best, len);
        }
        return best;
    }
};
