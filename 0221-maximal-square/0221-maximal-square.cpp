#include <vector>
#include <algorithm>

class Solution {
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        int max_side = 0;
        
        // DP table initialized to 0
        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] == '1') {
                    // For first row or first column, the max side can only be 1
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        // Look at top, left, and top-left neighbors
                        dp[i][j] = std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    }
                    max_side = std::max(max_side, dp[i][j]);
                }
            }
        }
        
        // Return the area of the largest square
        return max_side * max_side;
    }
};
