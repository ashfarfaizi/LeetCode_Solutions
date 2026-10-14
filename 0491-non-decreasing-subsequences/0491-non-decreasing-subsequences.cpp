#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }

private:
    void backtrack(const vector<int>& nums, int index, vector<int>& current, vector<vector<int>>& result) {
        // Condition: Add to results if the subsequence contains at least two elements
        if (current.size() >= 2) {
            result.push_back(current);
        }

        // Set to detect and skip duplicate elements *at the current recursion level*
        unordered_set<int> usedInThisLevel;

        for (int i = index; i < nums.size(); ++i) {
            // Rule 1: Maintain non-decreasing order
            if (!current.empty() && nums[i] < current.back()) {
                continue;
            }
            
            // Rule 2: Skip duplicates within the same sibling branch selection
            if (usedInThisLevel.count(nums[i])) {
                continue;
            }

            // Mark element as used and add to current path
            usedInThisLevel.insert(nums[i]);
            current.push_back(nums[i]);

            // Recurse to the next elements
            backtrack(nums, i + 1, current, result);

            // Backtrack: undo our selection
            current.pop_back();
        }
    }
};
