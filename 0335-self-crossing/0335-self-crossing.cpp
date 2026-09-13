#include <vector>

using namespace std;

class Solution {
public:
    bool isSelfCrossing(vector<int>& distance) {
        int n = distance.size();
        if (n < 4) return false; // Impossible to self-cross with less than 4 movements
        
        for (int i = 3; i < n; ++i) {
            // Case 1: Current line crosses the line from 3 steps ago
            if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3]) {
                return true;
            }
            
            // Case 2: Current line crosses the line from 4 steps ago
            if (i >= 4 && distance[i - 1] == distance[i - 3] && 
                distance[i] + distance[i - 4] >= distance[i - 2]) {
                return true;
            }
            
            // Case 3: Current line crosses the line from 5 steps ago
            if (i >= 5 && distance[i - 1] <= distance[i - 3] && 
                distance[i - 1] + distance[i - 5] >= distance[i - 3] && 
                distance[i - 2] >= distance[i - 4] && 
                distance[i] + distance[i - 4] >= distance[i - 2]) {
                return true;
            }
        }
        
        return false;
    }
};
