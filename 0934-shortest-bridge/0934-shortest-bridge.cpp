/*
 * Approach: find any land cell and flood-fill its island with DFS, marking
 * the cells as 2 and pushing them all into a queue. Then run a multi-source
 * BFS outward over water; the number of layers expanded before touching a
 * cell of the other island (still 1) is the number of flips needed.
 *
 * Time:  O(n^2)
 * Space: O(n^2)
 */
class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        queue<pair<int, int>> q;
        vector<pair<int, int>> stack;
        for (int r = 0; r < n && stack.empty(); ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    grid[r][c] = 2;
                    stack.push_back({r, c});
                    break;
                }
            }
        }
        while (!stack.empty()) {
            auto [r, c] = stack.back();
            stack.pop_back();
            q.push({r, c});
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    stack.push_back({nr, nc});
                }
            }
        }
        for (int steps = 0; !q.empty(); ++steps) {
            for (int sz = q.size(); sz > 0; --sz) {
                auto [r, c] = q.front();
                q.pop();
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n || grid[nr][nc] == 2) continue;
                    if (grid[nr][nc] == 1) return steps;
                    grid[nr][nc] = 2;
                    q.push({nr, nc});
                }
            }
        }
        return -1;
    }
};
