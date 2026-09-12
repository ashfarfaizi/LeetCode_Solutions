class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        // Initialize memoization table with 0 (unvisited status)
        vector<vector<int>> memo(m, vector<int>(n, 0));
        int max_path = 0;
        
        // Run DFS from every single cell in the matrix
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                max_path = max(max_path, dfs(matrix, i, j, memo));
            }
        }
        
        return max_path;
    }

private:
    // Direction vectors for moving: Up, Down, Left, Right
    const vector<int> dirs = {-1, 0, 1, 0, -1};

    int dfs(const vector<vector<int>>& matrix, int r, int c, vector<vector<int>>& memo) {
        // If already computed, return the cached result
        if (memo[r][c] != 0) return memo[r][c];
        
        int max_len = 1; // Every single cell has a path of length at least 1
        int m = matrix.size();
        int n = matrix[0].size();
        
        // Explore all 4 orthogonal directions
        for (int i = 0; i < 4; ++i) {
            int nr = r + dirs[i];
            int nc = c + dirs[i + 1];
            
            // Check boundary conditions and strict increasing rule
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && matrix[nr][nc] > matrix[r][c]) {
                max_len = max(max_len, 1 + dfs(matrix, nr, nc, memo));
            }
        }
        
        // Cache the result before returning
        return memo[r][c] = max_len;
    }
};
