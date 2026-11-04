/*
 * Approach: Greedy. After sorting, pairing neighbours (a0,a1), (a2,a3), ...
 * is optimal: the smallest element is always a pair minimum, and pairing it
 * with the next smallest wastes the least. Sum the even-indexed elements.
 * Time: O(n log n), Space: O(1) besides the sort
 */
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int sum = 0;
        for (size_t i = 0; i < nums.size(); i += 2) sum += nums[i];
        return sum;
    }
};
