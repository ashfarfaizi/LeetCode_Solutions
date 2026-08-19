#pragma GCC optimize ("O2")

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        // A row at index 'rowIndex' contains exactly (rowIndex + 1) elements.
        // Initialize all elements to 1 to handle boundary values automatically.
        vector<int> row(rowIndex + 1, 1);
        
        // Build the triangle rows incrementally up to the target rowIndex
        for (int i = 2; i <= rowIndex; ++i) {
            // Traverse backwards from the second-to-last element down to index 1.
            // Iterating backwards prevents overwriting elements from the previous row
            // state that are still needed for current additions.
            for (int j = i - 1; j >= 1; --j) {
                row[j] = row[j] + row[j - 1];
            }
        }
        
        return row;
    }
};
