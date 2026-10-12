#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

class Solution {
public:
    int findRadius(std::vector<int>& houses, std::vector<int>& heaters) {
        // Sort heaters to perform binary search (lower_bound)
        std::sort(heaters.begin(), heaters.end());
        
        int minRadius = 0;
        
        for (int house : houses) {
            // Find the first heater located at or to the right of the current house
            auto it = std::lower_bound(heaters.begin(), heaters.end(), house);
            
            int distToRightHeater = INT_MAX;
            int distToLeftHeater = INT_MAX;
            
            // If a heater exists at or to the right
            if (it != heaters.end()) {
                distToRightHeater = *it - house;
            }
            
            // If a heater exists to the left
            if (it != heaters.begin()) {
                distToLeftHeater = house - *(it - 1);
            }
            
            // The nearest heater to the current house is the minimum of both sides
            int closestHeaterDist = std::min(distToRightHeater, distToLeftHeater);
            
            // The global radius must cover the most poorly positioned house
            minRadius = std::max(minRadius, closestHeaterDist);
        }
        
        return minRadius;
    }
};
