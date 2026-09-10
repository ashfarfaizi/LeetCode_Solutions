#include <vector>
#include <climits>
#include <algorithm>

class Solution {
public:
    int nthSuperUglyNumber(int n, std::vector<int>& primes) {
        int k = primes.size();
        
        // Stores the first n super ugly numbers
        std::vector<long long> ugly(n); 
        ugly[0] = 1; // The first super ugly number is 1
        
        // Pointers for each prime to track its progress in the ugly array
        std::vector<int> pointers(k, 0); 
        
        for (int i = 1; i < n; ++i) {
            long long next_ugly = LLONG_MAX;
            
            // Find the minimum next possible ugly number
            for (int j = 0; j < k; ++j) {
                long long current_val = ugly[pointers[j]] * primes[j];
                if (current_val < next_ugly) {
                    next_ugly = current_val;
                }
            }
            
            ugly[i] = next_ugly;
            
            // Advance all pointers that generated the minimum value to avoid duplicates
            for (int j = 0; j < k; ++j) {
                if (ugly[pointers[j]] * primes[j] == next_ugly) {
                    pointers[j]++;
                }
            }
        }
        
        return static_cast<int>(ugly[n - 1]);
    }
};
