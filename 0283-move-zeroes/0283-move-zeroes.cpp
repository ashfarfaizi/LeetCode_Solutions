#include <vector>
#include <algorithm>

class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        int lastNonZeroFoundAt = 0;
        
        // Iterate through the array
        for (int i = 0; i < nums.size(); i++) {
            // Whenever we encounter a non-zero element, swap it with the pointer track
            if (nums[i] != 0) {
                std::swap(nums[lastNonZeroFoundAt], nums[i]);
                lastNonZeroFoundAt++;
            }
        }
    }
};
