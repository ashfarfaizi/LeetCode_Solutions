#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};
        
        int m = mat.size();
        int n = mat[0].size();
        
        // There are exactly (m + n - 1) diagonals
        vector<vector<int>> diagonals(m + n - 1);
        
        // Group elements by their coordinate sum (r + c)
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                diagonals[r + c].push_back(mat[r][c]);
            }
        }
        
        vector<int> result;
        for (int i = 0; i < diagonals.size(); ++i) {
            // Even diagonal indices need to be traversed upwards
            if (i % 2 == 0) {
                reverse(diagonals[i].begin(), diagonals[i].end());
            }
            
            // Collect the results
            for (int num : diagonals[i]) {
                result.push_back(num);
            }
        }
        
        return result;
    }
};
