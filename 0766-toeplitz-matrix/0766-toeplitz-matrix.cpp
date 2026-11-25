/*
 * Approach: A matrix is Toeplitz exactly when every cell outside the first
 * row and column equals its upper-left neighbour, so compare each
 * matrix[i][j] with matrix[i-1][j-1].
 *
 * Time:  O(m * n)
 * Space: O(1)
 */
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        for (size_t i = 1; i < matrix.size(); ++i) {
            for (size_t j = 1; j < matrix[i].size(); ++j) {
                if (matrix[i][j] != matrix[i - 1][j - 1]) return false;
            }
        }
        return true;
    }
};
