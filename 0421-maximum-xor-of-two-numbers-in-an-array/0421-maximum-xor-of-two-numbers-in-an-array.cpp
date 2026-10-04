#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int max_xor = 0;
        int mask = 0;
        
        // Iterate from the most significant bit (30) down to 0
        for (int i = 30; i >= 0; i--) {
            // Set the i-th bit in the mask to 1
            mask |= (1 << i);
            
            unordered_set<int> prefixes;
            // Store the prefixes of all numbers up to the i-th bit
            for (int num : nums) {
                prefixes.insert(num & mask);
            }
            
            // Greedily assume that the i-th bit of our max result can be 1
            int candidate_max = max_xor | (1 << i);
            
            // Check if there are two prefixes that can XOR to create candidate_max
            for (int prefix : prefixes) {
                if (prefixes.count(prefix ^ candidate_max)) {
                    max_xor = candidate_max;
                    break; // Found a valid pair, move to the next lower bit
                }
            }
        }
        
        return max_xor;
    }
};
