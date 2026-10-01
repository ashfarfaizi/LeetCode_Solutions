class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        
        int totalSlices = 0;
        int currentSlices = 0;
        
        // Loop from the 3rd element to the end
        for (int i = 2; i < n; ++i) {
            // Check if the current triplet forms an arithmetic sequence
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                currentSlices += 1;
                totalSlices += currentSlices;
            } else {
                currentSlices = 0; // Reset count if sequence breaks
            }
        }
        
        return totalSlices;
    }
};
