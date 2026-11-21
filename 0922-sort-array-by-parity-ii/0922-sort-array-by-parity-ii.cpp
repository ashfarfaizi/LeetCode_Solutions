/*
 * Approach: two pointers, one over even indices and one over odd indices.
 * Advance each past positions that already hold the right parity; when both
 * stop, the even slot holds an odd number and the odd slot an even one, so
 * swapping fixes both at once.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int n = nums.size();
        for (int even = 0, odd = 1; even < n && odd < n;) {
            if (nums[even] % 2 == 0) {
                even += 2;
            } else if (nums[odd] % 2 == 1) {
                odd += 2;
            } else {
                swap(nums[even], nums[odd]);
            }
        }
        return nums;
    }
};
