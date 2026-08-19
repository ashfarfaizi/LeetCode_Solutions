#pragma GCC optimize ("O2")

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;
        
        for (int i = 0; i < numRows; ++i) {
            // Allocate space for the row and initialize all entries to 1
            vector<int> row(i + 1, 1);
            
            // Populate the interior elements of the row
            // Each element is calculated by adding the two elements directly above it
            for (int j = 1; j < i; ++j) {
                row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
            
            // Append the fully constructed row to our results container
            triangle.push_back(row);
        }
        
        return triangle;
    }
};
