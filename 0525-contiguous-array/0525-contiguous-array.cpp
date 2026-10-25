class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        // Map to store the first occurrence of a specific running sum: {sum, index}
        unordered_map<int, int> sum_map;
        
        // Initialize with a sum of 0 at index -1 to handle subarrays starting from index 0
        sum_map[0] = -1;
        
        int max_len = 0;
        int running_sum = 0;
        
        for (int i = 0; i < nums.size(); ++i) {
            // Treat 0 as -1, and 1 as +1
            running_sum += (nums[i] == 1) ? 1 : -1;
            
            // If the running sum has been seen before, calculate the subarray length
            if (sum_map.find(running_sum) != sum_map.end()) {
                max_len = max(max_len, i - sum_map[running_sum]);
            } else {
                // Store the first time we see this sum
                sum_map[running_sum] = i;
            }
        }
        
        return max_len;
    }
};
