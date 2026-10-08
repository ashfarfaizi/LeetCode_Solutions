#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int minMoves(std::vector<int>& nums) {
        // Find the minimum element in the array
        int min_val = *std::min_element(nums.begin(), nums.end());
        
        int moves = 0;
        for (int num : nums) {
            moves += (num - min_val);
        }
        
        return moves;
    }
};
