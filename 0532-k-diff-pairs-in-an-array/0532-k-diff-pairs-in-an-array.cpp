#include <vector>
#include <unordered_map>

class Solution {
public:
    int findPairs(std::vector<int>& nums, int k) {
        // Step 1: Count the frequency of each number
        std::unordered_map<int, int> numCounts;
        for (int num : nums) {
            numCounts[num]++;
        }
        
        int pairCount = 0;
        
        // Step 2: Iterate through unique keys in the map
        for (const auto& [num, count] : numCounts) {
            if (k == 0) {
                // For k == 0, we need duplicates of the same number
                if (count >= 2) {
                    pairCount++;
                }
            } else {
                // For k > 0, check if (num + k) exists in the map
                if (numCounts.count(num + k)) {
                    pairCount++;
                }
            }
        }
        
        return pairCount;
    }
};
