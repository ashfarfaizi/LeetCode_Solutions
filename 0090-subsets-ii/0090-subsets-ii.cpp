#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> currentSubset;
        
        // Sorting helps to group duplicate elements together, which is crucial for deduplication
        std::sort(nums.begin(), nums.end());
        
        // Start backtracking from index 0
        backtrack(nums, 0, currentSubset, result);
        
        return result;
    }

private:
    void backtrack(const std::vector<int>& nums, int startIndex, std::vector<int>& currentSubset, std::vector<std::vector<int>>& result) {
        // Add the currently built subset to our final power set result
        result.push_back(currentSubset);
        
        for (int i = startIndex; i < nums.size(); ++i) {
            // If the current element is the same as the previous element and it's not the first 
            // element in this level of choice, skip it to avoid generating duplicate subsets
            if (i > startIndex && nums[i] == nums[i - 1]) {
                continue;
            }
            
            // Include the current element
            currentSubset.push_back(nums[i]);
            
            // Move to the next index recursively
            backtrack(nums, i + 1, currentSubset, result);
            
            // Backtrack: remove the last element to explore other combinations
            currentSubset.pop_back();
        }
    }
};
