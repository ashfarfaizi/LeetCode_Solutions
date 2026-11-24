/*
 * Approach: Dijkstra where a path's cost is the maximum edge weight on it
 * instead of the sum. effort[r][c] is the best known effort to reach a cell;
 * popping cells in increasing effort order guarantees the first time the
 * target is popped its effort is optimal.
 *
 * Time:  O(R * C * log(R * C))
 * Space: O(R * C)
 */
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size(), cols = heights[0].size();
        vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
        using State = tuple<int, int, int>;  // effort, row, col
        priority_queue<State, vector<State>, greater<State>> pq;
        effort[0][0] = 0;
        pq.emplace(0, 0, 0);
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (!pq.empty()) {
            auto [e, r, c] = pq.top();
            pq.pop();
            if (e > effort[r][c]) continue;
            if (r == rows - 1 && c == cols - 1) return e;
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                int ne = max(e, abs(heights[nr][nc] - heights[r][c]));
                if (ne < effort[nr][nc]) {
                    effort[nr][nc] = ne;
                    pq.emplace(ne, nr, nc);
                }
            }
        }
        return 0;
    }
};
