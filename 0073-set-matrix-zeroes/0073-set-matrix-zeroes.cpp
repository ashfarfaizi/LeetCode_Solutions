#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        bool first_row_zero = false;
        bool first_col_zero = false;

        // Step 1: Check if the first row has any zeros
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                first_row_zero = true;
                break;
            }
        }

        // Step 1: Check if the first column has any zeros
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                first_col_zero = true;
                break;
            }
        }

        // Step 2: Use the first row and column as markers for the inner matrix
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // Step 3: Update the inner matrix cells using the markers
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Step 4: Zero out the first row if flagged
        if (first_row_zero) {
            for (int j = 0; j < n; ++j) {
                matrix[0][j] = 0;
            }
        }

        // Step 4: Zero out the first column if flagged
        if (first_col_zero) {
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
    }
};
