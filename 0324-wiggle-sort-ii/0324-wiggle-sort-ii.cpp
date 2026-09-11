class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Create a sorted copy of the array
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        
        // Step 2: Set pointers at the end of the smaller half and larger half
        // For an array of size n, the smaller half ends at (n-1)/2
        int left = (n - 1) / 2; 
        int right = n - 1;
        
        // Step 3: Populate the original array from back to front
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                nums[i] = sorted_nums[left--];  // Put smaller elements at even indices
            } else {
                nums[i] = sorted_nums[right--]; // Put larger elements at odd indices
            }
        }
    }
};
