class Solution {
public:
    int rob(vector<int>& nums) {
        int prev1 = 0; // Max money if we rob up to the previous house
        int prev2 = 0; // Max money if we rob up to two houses ago
        
        for (int num : nums) {
            int current = max(prev1, prev2 + num);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};
