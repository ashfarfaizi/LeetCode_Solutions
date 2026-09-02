#include <vector>
#include <unordered_set>

class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
        std::unordered_set<int> window;
        
        for (int i = 0; i < nums.size(); ++i) {
            // Remove the element that is out of the sliding window range
            if (i > k) {
                window.erase(nums[i - k - 1]);
            }
            
            // If the element is already in the window, we found our duplicate
            if (window.find(nums[i]) != window.end()) {
                return true;
            }
            
            // Add the current element to the window
            window.insert(nums[i]);
        }
        
        return false;
    }
};
