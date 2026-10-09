#include <vector>

class Solution {
public:
    int islandPerimeter(std::vector<std::vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int islands = 0;
        int neighbours = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1) {
                    islands++; // Count total land cells
                    
                    // Check if the cell directly below is also land
                    if (i + 1 < rows && grid[i + 1][j] == 1) {
                        neighbours++;
                    }
                    // Check if the cell directly to the right is also land
                    if (j + 1 < cols && grid[i][j + 1] == 1) {
                        neighbours++;
                    }
                }
            }
        }
        
        // Total perimeter = (Land cells * 4) - (Shared edges * 2)
        return (islands * 4) - (neighbours * 2);
    }
};
