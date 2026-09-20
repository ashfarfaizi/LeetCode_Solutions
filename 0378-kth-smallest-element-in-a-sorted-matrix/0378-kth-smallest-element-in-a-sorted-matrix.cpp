#include <vector>

class Solution {
private:
    // Helper function to count elements <= target in O(n) time and O(1) space
    int countLessOrEqual(const std::vector<std::vector<int>>& matrix, int mid, int n) {
        int count = 0;
        int row = n - 1; // Start from bottom-left corner
        int col = 0;
        
        while (row >= 0 && col < n) {
            if (matrix[row][col] <= mid) {
                count += (row + 1); // Entire column from 0 to row is <= mid
                col++;
            } else {
                row--;
            }
        }
        return count;
    }

public:
    int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
        int n = matrix.size();
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];
        int ans = low;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (countLessOrEqual(matrix, mid, n) >= k) {
                ans = mid;       // mid is a candidate answer
                high = mid - 1;  // Try to find a smaller valid value
            } else {
                low = mid + 1;   // The value must be larger
            }
        }
        
        return ans;
    }
};
