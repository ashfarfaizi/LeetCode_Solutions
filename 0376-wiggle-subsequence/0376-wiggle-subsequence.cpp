#include <vector>

class Solution {
public:
    int wiggleMaxLength(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        
        int count = 1; // A single element is always a valid wiggle sequence
        int prediff = 0;
        
        for (size_t i = 1; i < nums.size(); ++i) {
            int currdiff = nums[i] - nums[i - 1];
            
            // Check if the direction has alternated
            if ((currdiff > 0 && prediff <= 0) || (currdiff < 0 && prediff >= 0)) {
                count++;
                prediff = currdiff; // Update the previous difference direction
            }
        }
        
        return count;
    }
};
