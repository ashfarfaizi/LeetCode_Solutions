#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int>> power_set;

    void backtrack(int start, const vector<int>& nums, vector<int>& current_subset) {
        // Every single state reached in the decision tree is a valid subset
        power_set.push_back(current_subset);

        for (int i = start; i < nums.size(); ++i) {
            // Step 1: Make a choice
            current_subset.push_back(nums[i]);

            // Step 2: Move deeper down the decision tree
            backtrack(i + 1, nums, current_subset);

            // Step 3: Undo the choice (Backtrack)
            current_subset.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        power_set.clear();
        vector<int> current_subset;
        backtrack(0, nums, current_subset);
        return power_set;
    }
};
