#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

class Solution {
private:
    std::vector<int> prefixSums;
    std::mt19937 gen; // High-quality random number generator (Mersenne Twister)

public:
    Solution(std::vector<int>& w) {
        // Step 1: Compute the prefix sum array
        int currentSum = 0;
        for (int weight : w) {
            currentSum += weight;
            prefixSums.push_back(currentSum);
        }
        
        // Step 2: Initialize the random seed
        std::random_device rd;
        gen.seed(rd());
    }
    
    int pickIndex() {
        // Step 3: Generate a random number in the range [1, total_sum]
        int totalSum = prefixSums.back();
        std::uniform_int_distribution<int> dist(1, totalSum);
        int target = dist(gen);
        
        // Step 4: Binary search to find the target target range
        // lower_bound finds the first element >= target
        auto it = std::lower_bound(prefixSums.begin(), prefixSums.end(), target);
        
        // Step 5: Convert the iterator back to its corresponding index
        return std::distance(prefixSums.begin(), it);
    }
};

