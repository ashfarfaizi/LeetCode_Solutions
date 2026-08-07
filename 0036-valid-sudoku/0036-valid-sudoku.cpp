#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // Bitmask arrays to track digits 1-9 for rows, columns, and 3x3 boxes
        int rows[9] = {0};
        int cols[9] = {0};
        int boxes[9] = {0};
        
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    continue;
                }
                
                int val = board[i][j] - '0';
                int digit_bit = 1 << (val - 1);
                int box_idx = (i / 3) * 3 + (j / 3);
                
                // Check if the digit has already appeared in the current row, column, or box
                if ((rows[i] & digit_bit) || (cols[j] & digit_bit) || (boxes[box_idx] & digit_bit)) {
                    return false;
                }
                
                // Mark the digit as seen by updating the masks
                rows[i] |= digit_bit;
                cols[j] |= digit_bit;
                boxes[box_idx] |= digit_bit;
            }
        }
        
        return true;
    }
};
