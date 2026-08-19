#pragma GCC optimize ("O2")

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        
        // Initialize our DP array with the values from the bottom-most row.
        // The bottom row contains exactly n elements.
        vector<int> dp = triangle[n - 1];
        
        // Walk upwards row-by-row, starting from the second-to-last row (n-2)
        for (int i = n - 2; i >= 0; --i) {
            // Sweep across all columns 'j' in the active row
            for (int j = 0; j <= i; ++j) {
                // The minimum path sum at cell (i, j) depends on the value of the cell
                // plus the minimum of the two accessible paths immediately beneath it.
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }
        
        // After fully converging to the apex, index 0 holds the minimum path sum
        return dp[0];
    }
};
