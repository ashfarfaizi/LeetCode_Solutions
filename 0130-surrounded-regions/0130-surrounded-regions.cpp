#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to mark border-connected 'O's with a placeholder '#'
    void dfs(vector<vector<char>>& board, int r, int c, int m, int n) {
        // Boundary and base case validations
        if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != 'O') {
            return;
        }

        // Temporarily modify the cell to prevent infinite loop cycles
        board[r][c] = '#';

        // Traverse in all 4 cardinal directions
        dfs(board, r + 1, c, m, n); // Down
        dfs(board, r - 1, c, m, n); // Up
        dfs(board, r, c + 1, m, n); // Right
        dfs(board, r, c - 1, m, n); // Left
    }

public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;

        int m = board.size();
        int n = board[0].size();

        // Step 1: Scan the first and last columns for border 'O's
        for (int r = 0; r < m; ++r) {
            if (board[r][0] == 'O') dfs(board, r, 0, m, n);
            if (board[r][n - 1] == 'O') dfs(board, r, n - 1, m, n);
        }

        // Step 2: Scan the first and last rows for border 'O's
        for (int c = 0; c < n; ++c) {
            if (board[0][c] == 'O') dfs(board, 0, c, m, n);
            if (board[m - 1][c] == 'O') dfs(board, m - 1, c, m, n);
        }

        // Step 3: Iterate through the grid to flip remaining regions
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (board[r][c] == 'O') {
                    // This 'O' is completely surrounded, flip to 'X'
                    board[r][c] = 'X';
                } else if (board[r][c] == '#') {
                    // This cell is border-connected, restore back to 'O'
                    board[r][c] = 'O';
                }
            }
        }
    }
};
