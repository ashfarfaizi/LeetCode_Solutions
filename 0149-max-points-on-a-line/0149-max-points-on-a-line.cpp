#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) return n; // Any 2 points or fewer will always form a line
        
        int global_max = 2;
        
        for (int i = 0; i < n; ++i) {
            unordered_map<string, int> slope_count;
            int local_max = 0;
            
            for (int j = i + 1; j < n; ++j) {
                int dy = points[j][1] - points[i][1];
                int dx = points[j][0] - points[i][0];
                
                // Reduce the fraction by finding the Greatest Common Divisor (GCD)
                int g = std::gcd(dy, dx);
                dy /= g;
                dx /= g;
                
                // Handle negative signs cleanly so (-1, 2) is the same as (1, -2)
                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                } else if (dx == 0) {
                    // Vertical line: ensure standard notation (1, 0)
                    dy = 1; 
                }
                
                // Represent slope as a string key "dy_dx"
                string slope = to_string(dy) + "_" + to_string(dx);
                slope_count[slope]++;
                local_max = max(local_max, slope_count[slope]);
            }
            // local_max counts other points. Add 1 to include the anchor point itself.
            global_max = max(global_max, local_max + 1);
        }
        
        return global_max;
    }
};
