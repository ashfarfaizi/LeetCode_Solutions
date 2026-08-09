#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;

        int m = matrix.size();
        int n = matrix[0].size();

        // Treat the 2D matrix as a single, virtual 1D sorted array
        int low = 0;
        int high = (m * n) - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // Map the virtual 1D index back to actual 2D row and column indexes
            int row = mid / n;
            int col = mid % n;
            int current_val = matrix[row][col];

            if (current_val == target) {
                return true;
            } else if (current_val < target) {
                low = mid + 1; // Target is in the right half
            } else {
                high = mid - 1; // Target is in the left half
            }
        }

        return false;
    }
};
