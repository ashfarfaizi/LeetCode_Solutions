#include <vector>
#include <unordered_map>
#include <cstdlib>

using namespace std;

class Solution {
private:
    unordered_map<int, int> flipped;
    int rows;
    int cols;
    int total_cells;

public:
    Solution(int m, int n) {
        rows = m;
        cols = n;
        total_cells = m * n;
    }
    
    vector<int> flip() {
        int r = rand() % total_cells;
        total_cells--;
        
        int actual_idx = r;
        if (flipped.count(r)) {
            actual_idx = flipped[r];
        }
        
        int last_idx = total_cells;
        if (flipped.count(last_idx)) {
            flipped[r] = flipped[last_idx];
        } else {
            flipped[r] = last_idx;
        }
        
        return {actual_idx / cols, actual_idx % cols};
    }
    
    void reset() {
        flipped.clear();
        total_cells = rows * cols;
    }
};
