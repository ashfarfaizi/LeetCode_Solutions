#include <vector>
#include <unordered_map>

class Solution {
public:
    int numberOfBoomerangs(std::vector<std::vector<int>>& points) {
        int totalBoomerangs = 0;
        
        // Iterate through each point, treating it as the pivot 'i'
        for (int i = 0; i < points.size(); ++i) {
            std::unordered_map<int, int> distanceCounts;
            
            // Calculate the distance from pivot 'i' to all other points 'j'
            for (int j = 0; j < points.size(); ++j) {
                if (i == j) continue; // Skip comparing a point to itself
                
                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];
                
                // Use squared distance to avoid floating-point inaccuracies from sqrt()
                int squaredDist = dx * dx + dy * dy;
                
                distanceCounts[squaredDist]++;
            }
            
            // For each unique distance, calculate how many permutations of pairs we can make
            for (auto& [distance, count] : distanceCounts) {
                if (count > 1) {
                    // If 'count' points have the same distance, we can pick any 2 in order: count * (count - 1)
                    totalBoomerangs += count * (count - 1);
                }
            }
        }
        
        return totalBoomerangs;
    }
};
