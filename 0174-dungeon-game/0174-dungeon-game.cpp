#include <vector>
#include <algorithm>

class Solution {
public:
    int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        
        // dp[i][j] represents the min health needed before entering room (i, j)
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        
        // Base Case: Calculate for the princess room (bottom-right corner)
        // If the room has a demon (negative), knight needs 1 + abs(dungeon value).
        // If it has a potion (positive), knight only needs 1 health point to step in.
        dp[m-1][n-1] = std::max(1, 1 - dungeon[m-1][n-1]);
        
        // Fill the last column (can only move DOWN from here)
        for (int i = m - 2; i >= 0; --i) {
            dp[i][n-1] = std::max(1, dp[i+1][n-1] - dungeon[i][n-1]);
        }
        
        // Fill the last row (can only move RIGHT from here)
        for (int j = n - 2; j >= 0; --j) {
            dp[m-1][j] = std::max(1, dp[m-1][j+1] - dungeon[m-1][j]);
        }
        
        // Fill the rest of the dungeon matrix
        for (int i = m - 2; i >= 0; --i) {
            for (int j = n - 2; j >= 0; --j) {
                // Knight chooses the optimal step: min health required between going right or down
                int min_health_next = std::min(dp[i+1][j], dp[i][j+1]);
                
                // Final calculation for current cell, ensuring it never drops below 1
                dp[i][j] = std::max(1, min_health_next - dungeon[i][j]);
            }
        }
        
        return dp[0][0];
    }
};
