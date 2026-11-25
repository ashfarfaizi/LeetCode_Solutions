/*
 * Approach: Multi-source BFS. Push every rotten orange as a level-0 source
 * and count the fresh ones. Process the queue level by level; each level is
 * one minute. When the queue drains, any remaining fresh orange is
 * unreachable.
 *
 * Time:  O(m * n)
 * Space: O(m * n) for the queue
 */
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), fresh = 0;
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) q.push({i, j});
                else if (grid[i][j] == 1) ++fresh;
            }
        }
        const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
        int minutes = 0;
        while (!q.empty() && fresh > 0) {
            for (int sz = q.size(); sz > 0; --sz) {
                auto [r, c] = q.front();
                q.pop();
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nc < 0 || nr >= m || nc >= n || grid[nr][nc] != 1) continue;
                    grid[nr][nc] = 2;
                    --fresh;
                    q.push({nr, nc});
                }
            }
            ++minutes;
        }
        return fresh == 0 ? minutes : -1;
    }
};
