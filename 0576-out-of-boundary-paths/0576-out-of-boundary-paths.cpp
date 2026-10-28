class Solution {
private:
    int MOD = 1e9 + 7;
    // 3D vector for memoization: memo[row][col][moves_left]
    vector<vector<vector<int>>> memo;

    int solve(int m, int n, int maxMove, int r, int c) {
        // Base Case 1: If the ball crosses the boundary, we found 1 valid path
        if (r < 0 || r >= m || c < 0 || c >= n) {
            return 1;
        }
        
        // Base Case 2: Out of moves and still inside the grid
        if (maxMove <= 0) {
            return 0;
        }
        
        // Return cached result if already calculated
        if (memo[r][c][maxMove] != -1) {
            return memo[r][c][maxMove];
        }
        
        // Explore all 4 adjacent directions
        long long paths = 0;
        paths += solve(m, n, maxMove - 1, r + 1, c); // Down
        paths += solve(m, n, maxMove - 1, r - 1, c); // Up
        paths += solve(m, n, maxMove - 1, r, c + 1); // Right
        paths += solve(m, n, maxMove - 1, r, c - 1); // Left
        
        // Store result with modulo operation
        return memo[r][c][maxMove] = paths % MOD;
    }

public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        // Initialize memoization table with -1
        memo.resize(m, vector<vector<int>>(n, vector<int>(maxMove + 1, -1)));
        
        return solve(m, n, maxMove, startRow, startColumn);
    }
};
