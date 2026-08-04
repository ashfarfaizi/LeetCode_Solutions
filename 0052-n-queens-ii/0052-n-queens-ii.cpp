class Solution {
public:
    int ans = 0;

    void backtrack(int row, int n, vector<int>& col,
                   vector<int>& diag1,
                   vector<int>& diag2) {
        if (row == n) {
            ans++;
            return;
        }

        for (int c = 0; c < n; c++) {
            if (col[c] || diag1[row - c + n - 1] || diag2[row + c])
                continue;

            col[c] = 1;
            diag1[row - c + n - 1] = 1;
            diag2[row + c] = 1;

            backtrack(row + 1, n, col, diag1, diag2);

            col[c] = 0;
            diag1[row - c + n - 1] = 0;
            diag2[row + c] = 0;
        }
    }

    int totalNQueens(int n) {
        vector<int> col(n, 0);
        vector<int> diag1(2 * n - 1, 0);
        vector<int> diag2(2 * n - 1, 0);

        backtrack(0, n, col, diag1, diag2);
        return ans;
    }
};