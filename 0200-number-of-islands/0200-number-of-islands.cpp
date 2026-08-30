class Solution {
private:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Base case: check boundary conditions and if the cell is water ('0')
        if (r < 0 || c < 0 || r >= m || c >= n || grid[r][c] == '0') {
            return;
        }
        
        // Mark the current land cell as visited by converting it to water ('0')
        grid[r][c] = '0';
        
        // Recursively visit all 4 adjacent directions (up, down, left, right)
        dfs(grid, r - 1, c); // Up
        dfs(grid, r + 1, c); // Down
        dfs(grid, r, c - 1); // Left
        dfs(grid, r, c + 1); // Right
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size();
        int n = grid[0].size();
        int island_count = 0;
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                // If we hit an unvisited piece of land ('1'), we found a new island
                if (grid[r][c] == '1') {
                    island_count++;
                    // Trigger DFS to sink the entire island
                    dfs(grid, r, c);
                }
            }
        }
        
        return island_count;
    }
};
