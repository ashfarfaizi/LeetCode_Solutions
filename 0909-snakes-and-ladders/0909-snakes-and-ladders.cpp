/*
 * Approach: breadth-first search over square numbers. From square s try the
 * six next squares, follow a snake or ladder if one starts there (only one
 * jump per move), and the first time the last square is dequeued gives the
 * minimum number of rolls. Square numbers are converted to (row, col) by
 * accounting for the alternating row direction.
 *
 * Time:  O(n^2)
 * Space: O(n^2)
 */
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size(), target = n * n;
        auto cell = [&](int s) -> int {
            int r = (s - 1) / n, c = (s - 1) % n;
            if (r % 2 == 1) c = n - 1 - c;
            return board[n - 1 - r][c];
        };
        vector<int> dist(target + 1, -1);
        queue<int> q;
        dist[1] = 0;
        q.push(1);
        while (!q.empty()) {
            int s = q.front();
            q.pop();
            if (s == target) return dist[s];
            for (int step = 1; step <= 6 && s + step <= target; ++step) {
                int next = s + step;
                int jump = cell(next);
                if (jump != -1) next = jump;
                if (dist[next] == -1) {
                    dist[next] = dist[s] + 1;
                    q.push(next);
                }
            }
        }
        return -1;
    }
};
