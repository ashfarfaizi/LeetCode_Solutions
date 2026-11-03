/*
 * Approach: Backtracking row by row. Track used columns and both diagonal
 * families (r - c + n - 1 and r + c) in boolean arrays so each placement
 * check is O(1). When all rows are filled, record the board.
 * Time: O(n!), Space: O(n^2) for the board plus O(n) bookkeeping
 */
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n, string(n, '.'));
        vector<bool> col(n), diag(2 * n - 1), anti(2 * n - 1);
        place(0, n, board, col, diag, anti, res);
        return res;
    }

private:
    void place(int r, int n, vector<string>& board, vector<bool>& col,
               vector<bool>& diag, vector<bool>& anti, vector<vector<string>>& res) {
        if (r == n) {
            res.push_back(board);
            return;
        }
        for (int c = 0; c < n; ++c) {
            int d = r - c + n - 1, a = r + c;
            if (col[c] || diag[d] || anti[a]) continue;
            col[c] = diag[d] = anti[a] = true;
            board[r][c] = 'Q';
            place(r + 1, n, board, col, diag, anti, res);
            board[r][c] = '.';
            col[c] = diag[d] = anti[a] = false;
        }
    }
};
