/*
 * Approach: Reverse the flow. Run a BFS from all Pacific border cells,
 * moving only "uphill" (to neighbours with height >= current), to mark every
 * cell that drains to the Pacific; do the same from the Atlantic border.
 * Cells marked by both searches are the answer.
 * Time: O(m*n), Space: O(m*n)
 */
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<char>> pac(m, vector<char>(n, 0)), atl(m, vector<char>(n, 0));
        queue<pair<int, int>> qp, qa;
        for (int r = 0; r < m; ++r) {
            mark(pac, qp, r, 0);
            mark(atl, qa, r, n - 1);
        }
        for (int c = 0; c < n; ++c) {
            mark(pac, qp, 0, c);
            mark(atl, qa, m - 1, c);
        }
        bfs(heights, pac, qp);
        bfs(heights, atl, qa);
        vector<vector<int>> res;
        for (int r = 0; r < m; ++r)
            for (int c = 0; c < n; ++c)
                if (pac[r][c] && atl[r][c]) res.push_back({r, c});
        return res;
    }

private:
    void mark(vector<vector<char>>& seen, queue<pair<int, int>>& q, int r, int c) {
        if (!seen[r][c]) {
            seen[r][c] = 1;
            q.push({r, c});
        }
    }

    void bfs(const vector<vector<int>>& h, vector<vector<char>>& seen, queue<pair<int, int>>& q) {
        static const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        int m = h.size(), n = h[0].size();
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nc < 0 || nr >= m || nc >= n) continue;
                if (h[nr][nc] < h[r][c]) continue;
                mark(seen, q, nr, nc);
            }
        }
    }
};
