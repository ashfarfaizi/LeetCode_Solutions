#include <bits/stdc++.h>

class Solution {
public:
    int totalHammingDistance(std::vector<int>& nums) {
        int totalDistance = 0;
        int n = nums.size();
        
        // Loop through each of the 32 possible bit positions
        for (int i = 0; i < 30; ++i) {
            int bitCountOnes = 0;
            
            // Count how many numbers have the i-th bit set
            for (int num : nums) {
                if ((num >> i) & 1) {
                    bitCountOnes++;
                }
            }
            
            // Contribution of the i-th bit to the total Hamming distance
            int bitCountZeros = n - bitCountOnes;
            totalDistance += bitCountOnes * bitCountZeros;
        }
        
        return totalDistance;
    }
};
