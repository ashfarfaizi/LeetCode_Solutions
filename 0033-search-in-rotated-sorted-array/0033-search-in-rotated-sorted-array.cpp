class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        
        // Define sentinel values to virtually straighten the rotated curve
        const int VIRTUAL_INF = 1e9;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // If we find an exact match, exit immediately
            if (nums[mid] == target) {
                return mid;
            }
            
            // Determine if the target and the current midpoint are in the same structural segment.
            // We use the first element of the array as our structural anchor.
            bool target_on_left = (target >= nums[0]);
            bool mid_on_left = (nums[mid] >= nums[0]);
            
            long long mapped_value = nums[mid];
            
            // If they are on opposite sides of the rotation inflection point, 
            // transform the midpoint value to a virtual infinity to flatten the search space.
            if (target_on_left != mid_on_left) {
                if (target_on_left) {
                    // Target is on the left side, but mid is on the right side.
                    // Map mid to positive infinity so the search space pushes left.
                    mapped_value = VIRTUAL_INF;
                } else {
                    // Target is on the right side, but mid is on the left side.
                    // Map mid to negative infinity so the search space pushes right.
                    mapped_value = -VIRTUAL_INF;
                }
            }
            
            // Standard, conditionless binary search execution over the mapped space
            if (mapped_value < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return -1;
    }
};
