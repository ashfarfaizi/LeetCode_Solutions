#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> summaryRanges(std::vector<int>& nums) {
        std::vector<std::string> result;
        int n = nums.size();
        
        for (int i = 0; i < n; ++i) {
            int start = nums[i];
            
            // Advance i as long as the next number is consecutive
            // Check (i + 1 < n) first to prevent out of bounds
            while (i + 1 < n && nums[i + 1] == nums[i] + 1) {
                i++;
            }
            
            int end = nums[i];
            
            // Format the range according to the rules
            if (start == end) {
                result.push_back(std::to_string(start));
            } else {
                result.push_back(std::to_string(start) + "->" + std::to_string(end));
            }
        }
        
        return result;
    }
};
