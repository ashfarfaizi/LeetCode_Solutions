class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Initialize a 1D DP table representing the previous row
        vector<int> dp(n, 0);
        
        // Base case: top-left corner initialization
        dp[0] = grid[0][0];
        
        // Fill out the first row (can only come from the left)
        for (int j = 1; j < n; ++j) {
            dp[j] = dp[j - 1] + grid[0][j];
        }
        
        // Process the rest of the grid row by row
        for (int i = 1; i < m; ++i) {
            // First element of the current row can only come from above
            dp[0] += grid[i][0];
            
            // Fill the rest of the current row
            for (int j = 1; j < n; ++j) {
                // Minimum of coming from above (dp[j]) or from the left (dp[j-1])
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }
        
        // Bottom-right corner holds the minimum path sum
        return dp[n - 1];
    }
};
