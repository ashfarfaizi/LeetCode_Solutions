class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int missing = n; // Start with n since the loop only goes up to n-1
        
        for (int i = 0; i < n; ++i) {
            missing ^= i ^ nums[i];
        }
        
        return missing;
    }
};
