/*
 * Approach: BFS from (0,0) over 8-directional moves; the first time the
 * bottom-right cell is dequeued its distance is the shortest path. Visited
 * cells are marked by overwriting them with 1.
 *
 * Time:  O(n^2)
 * Space: O(n^2) for the queue
 */
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0) return -1;
        queue<array<int, 3>> q;  // row, col, path length
        q.push({0, 0, 1});
        grid[0][0] = 1;
        while (!q.empty()) {
            auto [r, c, d] = q.front();
            q.pop();
            if (r == n - 1 && c == n - 1) return d;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    int nr = r + dr, nc = c + dc;
                    if (nr < 0 || nc < 0 || nr >= n || nc >= n || grid[nr][nc] != 0) continue;
                    grid[nr][nc] = 1;
                    q.push({nr, nc, d + 1});
                }
            }
        }
        return -1;
    }
};
