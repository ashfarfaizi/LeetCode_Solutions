/*
 * Approach: level-by-level BFS from the entrance, marking cells as walls once
 * visited. The first border cell popped (other than the entrance) is the
 * nearest exit.
 * Time: O(m * n), Space: O(m * n)
 */
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size(), n = maze[0].size();
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        maze[entrance[0]][entrance[1]] = '+';
        for (int steps = 1; !q.empty(); ++steps) {
            for (int i = q.size(); i > 0; --i) {
                auto [r, c] = q.front();
                q.pop();
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n || maze[nr][nc] == '+') continue;
                    if (nr == 0 || nr == m - 1 || nc == 0 || nc == n - 1) return steps;
                    maze[nr][nc] = '+';
                    q.push({nr, nc});
                }
            }
        }
        return -1;
    }
};
