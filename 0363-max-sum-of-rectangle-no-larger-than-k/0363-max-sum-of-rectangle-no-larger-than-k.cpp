#include <vector>
#include <set>
#include <climits>
#include <algorithm>

class Solution {
public:
    int maxSumSubmatrix(std::vector<std::vector<int>>& matrix, int k) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int m = matrix.size();
        int n = matrix[0].size();
        int maxSum = INT_MIN;
        
        // Optimize boundary allocation: loop over columns if rows > columns
        bool colIsSmaller = (n < m);
        int outerMax = colIsSmaller ? n : m;
        int innerMax = colIsSmaller ? m : n;
        
        for (int i = 0; i < outerMax; ++i) {
            // Stores cumulative sums for the inner dimension elements
            std::vector<int> sums(innerMax, 0);
            
            for (int j = i; j < outerMax; ++j) {
                for (int p = 0; p < innerMax; ++p) {
                    sums[p] += colIsSmaller ? matrix[p][j] : matrix[j][p];
                }
                
                // Find the max subarray sum <= k using std::set
                std::set<int> prefixSums;
                prefixSums.insert(0);
                int currentPrefixSum = 0;
                
                for (int sum : sums) {
                    currentPrefixSum += sum;
                    // Find target such that target >= currentPrefixSum - k
                    auto it = prefixSums.lower_bound(currentPrefixSum - k);
                    if (it != prefixSums.end()) {
                        maxSum = std::max(maxSum, currentPrefixSum - *it);
                    }
                    prefixSums.insert(currentPrefixSum);
                }
            }
        }
        
        return maxSum;
    }
};
