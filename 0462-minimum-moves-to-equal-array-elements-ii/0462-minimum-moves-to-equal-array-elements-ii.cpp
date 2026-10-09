#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    int minMoves2(std::vector<int>& nums) {
        // Sort the array to find the median
        std::sort(nums.begin(), nums.end());
        
        int median = nums[nums.size() / 2];
        int moves = 0;
        
        // Sum up the absolute differences from the median
        for (int num : nums) {
            moves += std::abs(num - median);
        }
        
        return moves;
    }
};
