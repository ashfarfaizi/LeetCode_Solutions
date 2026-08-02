class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        // Define explicit window thresholds for our jump tiers
        int current_layer_left = 0;
        int current_layer_right = 0;
        
        int jump_counter = 0;
        
        // Process jumps slice-by-slice until the right boundary clears the destination index
        while (current_layer_right < n - 1) {
            int maximum_forward_reach = 0;
            
            // Scan through all elements inside the current layer window
            for (int i = current_layer_left; i <= current_layer_right; ++i) {
                maximum_forward_reach = max(maximum_forward_reach, i + nums[i]);
            }
            
            // Advance the boundaries to create the next layer window
            current_layer_left = current_layer_right + 1;
            current_layer_right = maximum_forward_reach;
            
            // Increment the jump tier count as we move into a deeper level
            jump_counter++;
            
            // Protection fallback: if boundaries stall, breaking out avoids infinite cycles
            if (current_layer_left > current_layer_right) break;
        }
        
        return jump_counter;
    }
};
