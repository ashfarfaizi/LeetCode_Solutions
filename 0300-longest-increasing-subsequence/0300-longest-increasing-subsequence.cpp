#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        
        std::vector<int> tails;
        
        for (int x : nums) {
            // Find the position of the first element >= x
            auto it = std::lower_bound(tails.begin(), tails.end(), x);
            
            // If x is larger than any element in tails, append it
            if (it == tails.end()) {
                tails.push_back(x);
            } else {
                // Otherwise, replace the element to optimize the tail value
                *it = x;
            }
        }
        
        // The size of tails represents the length of the LIS
        return tails.size();
    }
};
