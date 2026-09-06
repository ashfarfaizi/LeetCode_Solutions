#include <vector>
#include <algorithm>

class Solution {
public:
    int nthUglyNumber(int n) {
        // dp vector to store the first n ugly numbers
        std::vector<int> ugly(n);
        ugly[0] = 1; // The first ugly number is 1
        
        // Pointers for multiples of 2, 3, and 5
        int p2 = 0, p3 = 0, p5 = 0;
        
        for (int i = 1; i < n; ++i) {
            // Compute candidate next ugly numbers
            int next2 = ugly[p2] * 2;
            int next3 = ugly[p3] * 3;
            int next5 = ugly[p5] * 5;
            
            // The next ugly number is the smallest among the candidates
            int next_ugly = std::min({next2, next3, next5});
            ugly[i] = next_ugly;
            
            // Advance the pointer(s) that achieved the minimum
            if (next_ugly == next2) p2++;
            if (next_ugly == next3) p3++;
            if (next_ugly == next5) p5++;
        }
        
        return ugly[n - 1];
    }
};
