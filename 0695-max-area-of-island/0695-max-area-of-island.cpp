/*
 * Approach: For each unvisited land cell, run an iterative DFS that sinks the
 * island (sets cells to 0) while counting its cells; keep the largest count.
 * Time: O(m*n), Space: O(m*n) for the stack in the worst case
 */
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), best = 0;
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 1) continue;
                int area = 0;
                vector<pair<int, int>> st{{i, j}};
                grid[i][j] = 0;
                while (!st.empty()) {
                    auto [r, c] = st.back();
                    st.pop_back();
                    ++area;
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                            grid[nr][nc] = 0;
                            st.push_back({nr, nc});
                        }
                    }
                }
                best = max(best, area);
            }
        }
        return best;
    }
};
