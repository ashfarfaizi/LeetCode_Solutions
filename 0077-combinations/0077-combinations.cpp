#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int>> result;

    void backtrack(int start, int n, int k, vector<int>& current_path) {
        // Base Case: If the combination is of required length k, record it
        if (current_path.size() == k) {
            result.push_back(current_path);
            return;
        }

        // Pruning Optimization: Ensure there are enough elements left to form a valid combination
        int remaining_slots_needed = k - current_path.size();
        int upper_bound = n - remaining_slots_needed + 1;

        for (int i = start; i <= upper_bound; ++i) {
            // Step 1: Make a choice
            current_path.push_back(i);

            // Step 2: Recurse with the next integer to build the suffix combination
            backtrack(i + 1, n, k, current_path);

            // Step 3: Undo the choice (Backtrack)
            current_path.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        result.clear();
        vector<int> current_path;
        backtrack(1, n, k, current_path);
        return result;
    }
};
