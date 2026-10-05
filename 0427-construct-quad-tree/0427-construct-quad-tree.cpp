class Solution {
public:
    Node* constructQuadTree(vector<vector<int>>& grid, int rowStart, int rowEnd, int colStart, int colEnd) {
        int initialValue = grid[rowStart][colStart];
        bool allSame = true;
        
        for (int i = rowStart; i <= rowEnd; ++i) {
            for (int j = colStart; j <= colEnd; ++j) {
                if (grid[i][j] != initialValue) {
                    allSame = false;
                    break;
                }
            }
            if (!allSame) break;
        }
        
        if (allSame) {
            return new Node(initialValue == 1, true);
        }
        
        int rowMid = rowStart + (rowEnd - rowStart) / 2;
        int colMid = colStart + (colEnd - colStart) / 2;
        
        Node* node = new Node(true, false); 
        
        node->topLeft = constructQuadTree(grid, rowStart, rowMid, colStart, colMid);
        node->topRight = constructQuadTree(grid, rowStart, rowMid, colMid + 1, colEnd);
        node->bottomLeft = constructQuadTree(grid, rowMid + 1, rowEnd, colStart, colMid);
        node->bottomRight = constructQuadTree(grid, rowMid + 1, rowEnd, colMid + 1, colEnd);
        
        return node;
    }
    
    Node* construct(vector<vector<int>>& grid) {
        // FIXED: Using .size() instead of .length()
        int n = grid.size(); 
        if (n == 0) return NULL;
        return constructQuadTree(grid, 0, n - 1, 0, n - 1);
    }
};
