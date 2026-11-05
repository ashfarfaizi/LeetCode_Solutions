/*
 * Approach: BFS from the starting pixel, recolouring every 4-directionally
 * connected pixel that has the original colour. If the new colour equals the
 * original one there is nothing to do (and skipping avoids an infinite loop).
 * Time: O(m*n), Space: O(m*n)
 */
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int orig = image[sr][sc];
        if (orig == color) return image;
        int m = image.size(), n = image[0].size();
        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = color;
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && image[nr][nc] == orig) {
                    image[nr][nc] = color;
                    q.push({nr, nc});
                }
            }
        }
        return image;
    }
};
