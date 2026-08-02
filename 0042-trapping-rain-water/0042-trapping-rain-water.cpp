class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        
        int n = height.size();
        
        // Step 1: Locate the index of the absolute tallest bar in the terrain.
        // This structural dividing point breaks the problem into two distinct geometric halves.
        int global_max_idx = 0;
        for (int i = 1; i < n; ++i) {
            if (height[i] > height[global_max_idx]) {
                global_max_idx = i;
            }
        }
        
        int trapped_water_volume = 0;
        
        // Step 2: Unidirectional scanning phase for the left half.
        // The highest wall to the right is guaranteed to be >= running_left_max because of global_max_idx.
        int running_left_max = 0;
        for (int i = 0; i < global_max_idx; ++i) {
            if (height[i] > running_left_max) {
                running_left_max = height[i];
            } else {
                trapped_water_volume += (running_left_max - height[i]);
            }
        }
        
        // Step 3: Unidirectional scanning phase for the right half.
        // The highest wall to the left is guaranteed to be >= running_right_max because of global_max_idx.
        int running_right_max = 0;
        for (int i = n - 1; i > global_max_idx; --i) {
            if (height[i] > running_right_max) {
                running_right_max = height[i];
            } else {
                trapped_water_volume += (running_right_max - height[i]);
            }
        }
        
        return trapped_water_volume;
    }
};
