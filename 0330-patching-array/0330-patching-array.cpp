class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        // Use long long for 'miss' to prevent integer overflow when doubling
        long long miss = 1;
        int patches = 0;
        int i = 0;
        
        while (miss <= n) {
            // Case 1: The current element can help extend our continuous range
            if (i < nums.size() && nums[i] <= miss) {
                miss += nums[i];
                i++;
            } 
            // Case 2: There is a gap, so we greedily patch the value 'miss'
            else {
                miss += miss;
                patches++;
            }
        }
        
        return patches;
    }
};
