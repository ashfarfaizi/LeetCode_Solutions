#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to find either the first or last bound of a target
    int findBound(const vector<int>& nums, int target, bool findFirst) {
        int left = 0;
        int right = nums.size() - 1;
        int bound = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                bound = mid; // Record potential match
                if (findFirst) {
                    right = mid - 1; // Look left for the starting position
                } else {
                    left = mid + 1;  // Look right for the ending position
                }
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return bound;
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int firstPos = findBound(nums, target, true);
        
        // If the target is not found in the array, return early
        if (firstPos == -1) {
            return {-1, -1};
        }
        
        int lastPos = findBound(nums, target, false);
        return {firstPos, lastPos};
    }
};
