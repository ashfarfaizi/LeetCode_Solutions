#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        
        // If the grid is smaller than 3x3, it cannot trap any water inside
        if (m < 3 || n < 3) return 0;
        
        // Min-heap to store: {height, {row, col}}
        priority_queue<pair<int, pair<int, int>>, 
                       vector<pair<int, pair<int, int>>>, 
                       greater<pair<int, pair<int, int>>>> minHeap;
                       
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        // Step 1: Push all boundary cells into the min-heap
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    minHeap.push({heightMap[i][j], {i, j}});
                    visited[i][j] = true;
                }
            }
        }
        
        int totalWater = 0;
        int maxBoundaryHeight = 0;
        
        // Direction vectors for moving up, down, left, right
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Step 2: Process cells from the lowest boundary inward
        while (!minHeap.empty()) {
            auto curr = minHeap.top();
            minHeap.pop();
            
            int height = curr.first;
            int r = curr.second.first;
            int c = curr.second.second;
            
            // Maintain the maximum height boundary encountered so far
            maxBoundaryHeight = max(maxBoundaryHeight, height);
            
            // Explore all 4 neighbors
            for (int i = 0; i < 4; ++i) {
                int nr = r + dirs[i][0];
                int nc = c + dirs[i][1];
                
                // Check grid boundaries and whether the neighbor has been visited
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    
                    // If neighbor is lower than the current boundary wall, water is trapped
                    if (heightMap[nr][nc] < maxBoundaryHeight) {
                        totalWater += maxBoundaryHeight - heightMap[nr][nc];
                    }
                    
                    // Push neighbor into the heap with its effective height
                    minHeap.push({max(heightMap[nr][nc], maxBoundaryHeight), {nr, nc}});
                }
            }
        }
        
        return totalWater;
    }
};
