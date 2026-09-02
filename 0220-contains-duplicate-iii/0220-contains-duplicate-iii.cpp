#include <vector>
#include <set>
#include <cmath>

class Solution {
public:
    bool containsNearbyAlmostDuplicate(std::vector<int>& nums, int indexDiff, int valueDiff) {
        std::set<long long> window; // Use long long to prevent integer overflow
        
        for (int i = 0; i < nums.size(); ++i) {
            // Remove the element that falls out of the allowed sliding window range
            if (i > indexDiff) {
                window.erase(nums[i - indexDiff - 1]);
            }
            
            // Find the successor of nums[i] - valueDiff
            auto it = window.lower_bound((long long)nums[i] - valueDiff);
            
            // Check if successor exists and is within the ceiling limit nums[i] + valueDiff
            if (it != window.end() && *it <= (long long)nums[i] + valueDiff) {
                return true;
            }
            
            // Insert current element into the active window
            window.insert(nums[i]);
        }
        
        return false;
    }
};
