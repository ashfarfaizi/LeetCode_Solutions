class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        long long sum = 0;
        long long f = 0;
        int n = nums.size();
        
        // Step 1: Compute the initial sum of elements and F(0)
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            f += (long long)i * nums[i];
        }
        
        long long max_val = f;
        
        // Step 2: Dynamically calculate F(k) from F(k-1)
        for (int k = 1; k < n; ++k) {
            f = f + sum - (long long)n * nums[n - k];
            max_val = max(max_val, f);
        }
        
        return max_val;
    }
};
