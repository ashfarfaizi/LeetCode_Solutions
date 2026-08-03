class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n <= 1) return;
        
        // Step 1: Horizontal Line Symmetric Flip (Upside-Down Row Reflection)
        // This swaps top rows with bottom rows relative to the horizontal midpoint.
        int top_row_ptr = 0;
        int bottom_row_ptr = n - 1;
        
        while (top_row_ptr < bottom_row_ptr) {
            // Swap entire memory records in a single line sweep
            matrix[top_row_ptr].swap(matrix[bottom_row_ptr]);
            top_row_ptr++;
            bottom_row_ptr--;
        }
        
        // Step 2: Main-Diagonal Cell Symmetric Transposition
        // Reflect elements across the main diagonal (top-left to bottom-right).
        // By restricting 'j' to always start at 'i + 1', we only process cells 
        // strictly above the diagonal line, avoiding redundant reverse swaps.
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int backup_temp_cell = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = backup_temp_cell;
            }
        }
    }
};
