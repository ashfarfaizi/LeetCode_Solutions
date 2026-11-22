/*
 * Approach: backtracking DFS. Count the non-obstacle cells first, then walk
 * from the start in four directions, marking cells visited as we go and
 * unmarking on return. Reaching the end counts as a path only when every
 * walkable cell has been visited. The grid has at most 20 cells, so the
 * exhaustive search is fast.
 *
 * Time:  O(3^(R*C)) worst case
 * Space: O(R*C) recursion depth
 */
class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int sr = 0, sc = 0, empty = 0;
        for (int r = 0; r < (int)grid.size(); ++r)
            for (int c = 0; c < (int)grid[0].size(); ++c) {
                if (grid[r][c] != -1) ++empty;
                if (grid[r][c] == 1) sr = r, sc = c;
            }
        return dfs(grid, sr, sc, empty);
    }

private:
    int dfs(vector<vector<int>>& g, int r, int c, int remaining) {
        if (r < 0 || c < 0 || r >= (int)g.size() || c >= (int)g[0].size() || g[r][c] == -1)
            return 0;
        if (g[r][c] == 2) return remaining == 1 ? 1 : 0;
        int saved = g[r][c];
        g[r][c] = -1;
        int paths = dfs(g, r + 1, c, remaining - 1) + dfs(g, r - 1, c, remaining - 1) +
                    dfs(g, r, c + 1, remaining - 1) + dfs(g, r, c - 1, remaining - 1);
        g[r][c] = saved;
        return paths;
    }
};
