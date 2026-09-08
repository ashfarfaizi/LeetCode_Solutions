#include <vector>

class NumArray {
private:
    std::vector<int> prefixSums;

public:
    NumArray(std::vector<int>& nums) {
        int n = nums.size();
        // Size is n + 1 to easily handle the boundary condition when left = 0
        prefixSums.resize(n + 1, 0);
        
        // Build the cumulative prefix sum array
        for (int i = 0; i < n; ++i) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        // Constant time lookup
        return prefixSums[right + 1] - prefixSums[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
