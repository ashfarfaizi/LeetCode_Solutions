#include <vector>

class Solution {
private:
    // Helper array to easily iterate through all 8 directions
    const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    void dfs(std::vector<std::vector<char>>& board, int r, int c, int m, int n) {
        // Count how many mines are adjacent to the current cell (r, c)
        int mineCount = 0;
        for (const auto& dir : directions) {
            int nr = r + dir.first;
            int nc = c + dir.second;
            
            // If the neighbor is valid and contains a mine 'M'
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                if (board[nr][nc] == 'M') {
                    mineCount++;
                }
            }
        }

        if (mineCount > 0) {
            // Rule 3: If there are adjacent mines, turn into a digit and stop exploring
            board[r][c] = '0' + mineCount;
        } else {
            // Rule 2: If there are no adjacent mines, turn into 'B' and recurse
            board[r][c] = 'B';
            for (const auto& dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;
                
                // Only recursively visit unrevealed empty squares ('E')
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'E') {
                    // Mark it temporarily to prevent duplicate visits in the call stack
                    board[nr][nc] = 'B'; 
                    dfs(board, nr, nc, m, n);
                }
            }
        }
    }

public:
    std::vector<std::vector<char>> updateBoard(std::vector<std::vector<char>>& board, std::vector<int>& click) {
        int r = click[0];
        int c = click[1];
        int m = board.size();
        int n = board[0].size();

        // Rule 1: Clicked directly on a mine
        if (board[r][c] == 'M') {
            board[r][c] = 'X';
            return board;
        }

        // Start DFS if clicked on an unrevealed empty square ('E')
        if (board[r][c] == 'E') {
            dfs(board, r, c, m, n);
        }

        return board;
    }
};
