#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool dfs(int index, const vector<int>& matchsticks, vector<int>& sides, int target) {
        // Base Case: All matchsticks successfully assigned
        if (index == matchsticks.size()) {
            return sides[0] == target && sides[1] == target && sides[2] == target;
        }
        
        int current_stick = matchsticks[index];
        
        // Try placing the current matchstick into each of the 4 sides
        for (int i = 0; i < 4; ++i) {
            // Prune: if adding the stick exceeds the target side length
            if (sides[i] + current_stick > target) continue;
            
            // Prune: avoid duplicate work for identical side configurations
            bool duplicate_found = false;
            for (int j = 0; j < i; ++j) {
                if (sides[j] == sides[i]) {
                    duplicate_found = true;
                    break;
                }
            }
            if (duplicate_found) continue;
            
            // Backtracking step
            sides[i] += current_stick;
            if (dfs(index + 1, matchsticks, sides, target)) {
                return true;
            }
            sides[i] -= current_stick; // Undo choice
        }
        
        return false;
    }

public:
    bool makesquare(vector<int>& matchsticks) {
        if (matchsticks.size() < 4) return false;
        
        long long total_sum = accumulate(matchsticks.begin(), matchsticks.end(), 0LL);
        if (total_sum % 4 != 0) return false;
        
        int target_side_len = total_sum / 4;
        
        // Sort in descending order to optimize backtracking path branch pruning
        sort(matchsticks.rbegin(), matchsticks.rend());
        
        // If the single largest matchstick exceeds target side length, abort early
        if (matchsticks[0] > target_side_len) return false;
        
        vector<int> sides(4, 0);
        return dfs(0, matchsticks, sides, target_side_len);
    }
};
