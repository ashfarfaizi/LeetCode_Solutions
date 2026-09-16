#include <vector>
#include <algorithm>

class Solution {
public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
        // Step 1: Sort by width ascending, and height descending if widths match
        std::sort(envelopes.begin(), envelopes.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1]; // Height descending
            }
            return a[0] < b[0]; // Width ascending
        });
        
        // Step 2: Find the Longest Increasing Subsequence (LIS) on heights
        std::vector<int> lis;
        
        for (const auto& env : envelopes) {
            int height = env[1];
            
            // Find the insertion index using binary search
            auto it = std::lower_bound(lis.begin(), lis.end(), height);
            
            if (it == lis.end()) {
                lis.push_back(height); // Extend the sequence
            } else {
                *it = height; // Replace element to maintain a smaller boundary
            }
        }
        
        return lis.size();
    }
};
