#include <vector>

class Solution {
private:
    void backtrack(int k, int target, int start, std::vector<int>& current, std::vector<std::vector<int>>& result) {
        // Base case: If we have picked exactly k numbers
        if (current.size() == k) {
            // If the current combination sums up to n, add it to results
            if (target == 0) {
                result.push_back(current);
            }
            return;
        }
        
        // Pruning: If the target goes negative or we can't possibly pick enough elements, stop early
        if (target < 0) return;

        // Iterate through valid digits from 'start' to 9
        for (int i = start; i <= 9; ++i) {
            // Include the current number
            current.push_back(i);
            
            // Recurse with updated remaining sum (target - i) and next number (i + 1)
            backtrack(k, target - i, i + 1, current, result);
            
            // Backtrack: remove the last number to try other combinations
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combinationSum3(int k, int n) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        // Start backtracking from number 1
        backtrack(k, n, 1, current, result);
        
        return result;
    }
};
