#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> constructRectangle(int area) {
        // Start from the integer square root of area moving downwards
        int w = sqrt(area);
        
        // Find the first integer that perfectly divides the area
        while (area % w != 0) {
            w--;
        }
        
        // Since we started from sqrt(area) and went down, 
        // area / w is guaranteed to be >= w
        return {area / w, w};
    }
};
