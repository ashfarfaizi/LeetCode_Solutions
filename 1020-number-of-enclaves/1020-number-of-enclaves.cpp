/*
 * Approach: flood-fill (BFS) from every boundary land cell and sink it;
 * whatever land remains is enclosed.
 * Time: O(m*n)   Space: O(m*n) for the queue in the worst case
 */
class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        auto push = [&](int r, int c) {
            if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == 1) {
                grid[r][c] = 0;
                q.push({r, c});
            }
        };
        for (int i = 0; i < m; i++) { push(i, 0); push(i, n - 1); }
        for (int j = 0; j < n; j++) { push(0, j); push(m - 1, j); }
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (int k = 0; k < 4; k++) push(r + dr[k], c + dc[k]);
        }
        int cnt = 0;
        for (auto& row : grid) cnt += count(row.begin(), row.end(), 1);
        return cnt;
    }
};
