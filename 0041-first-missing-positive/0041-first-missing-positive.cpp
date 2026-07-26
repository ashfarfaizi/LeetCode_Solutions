class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();

        int pos = 0;

        while (pos < n) {
            int value = nums[pos];

            if (value > 0 &&
                value <= n &&
                nums[value - 1] != value) {

                swap(nums[pos], nums[value - 1]);
            } 
            else {
                ++pos;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1)
                return i + 1;
        }

        return n + 1;
    }
};