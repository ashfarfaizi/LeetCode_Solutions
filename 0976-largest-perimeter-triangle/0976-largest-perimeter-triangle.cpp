/*
 * Approach: sort descending and scan consecutive triples. For a fixed longest
 * side a, the best chance of satisfying b + c > a with the largest perimeter
 * is to take the next two largest values, so the first consecutive triple
 * that forms a valid triangle gives the answer. Return 0 if none does.
 *
 * Time:  O(n log n)
 * Space: O(1) extra (in-place sort)
 */
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.rbegin(), nums.rend());
        for (size_t i = 0; i + 2 < nums.size(); ++i)
            if (nums[i + 1] + nums[i + 2] > nums[i]) return nums[i] + nums[i + 1] + nums[i + 2];
        return 0;
    }
};
