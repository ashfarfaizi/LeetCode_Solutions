#include <vector>

class Solution {
public:
    int singleNonDuplicate(std::vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;
        
        while (low < high) {
            int mid = low + (high - low) / 2;
            
            // mid ^ 1 matches an even index to mid + 1, and an odd index to mid - 1
            if (nums[mid] == nums[mid ^ 1]) {
                // If they match, the single element lies in the right partition
                low = mid + 1;
            } else {
                // If they don't match, the single element lies in the left partition (or is mid itself)
                high = mid;
            }
        }
        
        return nums[low];
    }
};
