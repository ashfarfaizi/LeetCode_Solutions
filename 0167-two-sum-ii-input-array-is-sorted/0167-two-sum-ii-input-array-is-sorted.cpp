#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        // Initialize one pointer at the start and one at the end
        int left = 0;
        int right = numbers.size() - 1;
        
        while (left < right) {
            int current_sum = numbers[left] + numbers[right];
            
            if (current_sum == target) {
                // Problem states 1-indexed output
                return {left + 1, right + 1};
            }
            else if (current_sum < target) {
                // Sum is too small, increase the lower value
                left++;
            }
            else {
                // Sum is too large, decrease the higher value
                right--;
            }
        }
        
        // Fallback return statement (guaranteed to have exactly one solution)
        return {};
    }
};
