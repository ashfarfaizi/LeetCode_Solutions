class Solution {
private:
    // Helper function to check if a max sum of 'maxSum' is achievable with <= k subarrays
    bool canSplit(const vector<int>& nums, int k, int maxSum) {
        int currentSubarraySum = 0;
        int requiredSplits = 1; // Start with the first subarray
        
        for (int num : nums) {
            if (currentSubarraySum + num > maxSum) {
                // If adding num exceeds maxSum, start a new subarray
                currentSubarraySum = num;
                requiredSplits++;
                
                // If we need more than k subarrays, this maxSum is too small
                if (requiredSplits > k) {
                    return false;
                }
            } else {
                currentSubarraySum += num;
            }
        }
        return true;
    }

public:
    int splitArray(vector<int>& nums, int k) {
        int low = 0;
        int high = 0;
        
        for (int num : nums) {
            low = max(low, num); // Max single element
            high += num;         // Sum of all elements
        }
        
        int ans = high;
        
        // Binary search for the minimized largest sum
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (canSplit(nums, k, mid)) {
                ans = mid;        // 'mid' is possible, record it
                high = mid - 1;   // Try to find a smaller maximum sum
            } else {
                low = mid + 1;    // 'mid' is too small, increase the allowed sum
            }
        }
        
        return ans;
    }
};
