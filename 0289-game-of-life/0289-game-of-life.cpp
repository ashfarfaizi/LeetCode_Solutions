#include <vector>
#include <cmath>

class Solution {
public:
    void gameOfLife(std::vector<std::vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        
        // 8-directional offsets for neighbors
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        // First Pass: Encode state transitions
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                int liveNeighbors = 0;
                
                // Count active neighbors
                for (int i = 0; i < 8; ++i) {
                    int nr = r + dx[i];
                    int nc = c + dy[i];
                    
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        // 1 and 2 both represent cells that were originally ALIVE
                        if (board[nr][nc] == 1 || board[nr][nc] == 2) {
                            liveNeighbors++;
                        }
                    }
                }
                
                // Apply rules
                if (board[r][c] == 1) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        board[r][c] = 2; // Live -> Dead
                    }
                } else if (board[r][c] == 0) {
                    if (liveNeighbors == 3) {
                        board[r][c] = 3; // Dead -> Live
                    }
                }
            }
        }
        
        // Second Pass: Clean up placeholders to finalize the next generation
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (board[r][c] == 2) board[r][c] = 0;
                else if (board[r][c] == 3) board[r][c] = 1;
            }
        }
    }
};
