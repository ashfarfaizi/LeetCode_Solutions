#include <vector>

class Solution {
public:
    int majorityElement(std::vector<int>& nums) {
        int candidate = 0;
        int count = 0;
        
        for (int num : nums) {
            // If count falls to 0, pick the current element as the new candidate
            if (count == 0) {
                candidate = num;
            }
            
            // Add 1 if the current element matches the candidate, otherwise subtract 1
            if (num == candidate) {
                count++;
            } else {
                count--;
            }
        }
        
        // The problem guarantees that a majority element always exists
        return candidate;
    }
};
