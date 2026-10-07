class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        
        for (int i = 0; i < nums.size(); ++i) {
            // Get the index this value maps to (use abs because it might be negated)
            int index = abs(nums[i]) - 1;
            
            // If the value at that index is already negative, it's a duplicate
            if (nums[index] < 0) {
                result.push_back(index + 1);
            } else {
                // Otherwise, flip the sign to mark it as visited
                nums[index] = -nums[index];
            }
        }
        
        return result;
    }
};
