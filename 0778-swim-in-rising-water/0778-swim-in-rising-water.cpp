/*
 * Approach: Dijkstra-style search where the cost of a path is the maximum
 * elevation on it. A min-heap always expands the reachable cell with the
 * lowest required water level; the level at which the bottom-right cell is
 * popped is the answer.
 * Time: O(n^2 log n), Space: O(n^2)
 */
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<bool>> seen(n, vector<bool>(n, false));
        using State = tuple<int, int, int>;  // level, row, col
        priority_queue<State, vector<State>, greater<State>> pq;
        pq.emplace(grid[0][0], 0, 0);
        seen[0][0] = true;
        const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};

        while (!pq.empty()) {
            auto [level, r, c] = pq.top();
            pq.pop();
            if (r == n - 1 && c == n - 1) return level;
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nc < 0 || nr >= n || nc >= n || seen[nr][nc]) continue;
                seen[nr][nc] = true;
                pq.emplace(max(level, grid[nr][nc]), nr, nc);
            }
        }
        return -1;
    }
};
