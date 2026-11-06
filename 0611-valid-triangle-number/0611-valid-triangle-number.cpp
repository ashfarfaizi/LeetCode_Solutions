/*
 * Approach: Sort, then fix the largest side c = nums[k] and use two pointers
 * i < j < k. If nums[i] + nums[j] > c, every index from i..j-1 also works
 * with j, so add j - i and move j left; otherwise move i right.
 * Time: O(n^2), Space: O(1) besides sorting
 */
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int count = 0;
        for (int k = (int)nums.size() - 1; k >= 2; --k) {
            int i = 0, j = k - 1;
            while (i < j) {
                if (nums[i] + nums[j] > nums[k]) {
                    count += j - i;
                    --j;
                } else {
                    ++i;
                }
            }
        }
        return count;
    }
};
