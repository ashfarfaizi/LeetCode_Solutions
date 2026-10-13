#include <string>
#include <cmath>

class Solution {
public:
    std::string smallestGoodBase(std::string n_str) {
        unsigned long long n = std::stoull(n_str);
        
        // Iterate over the number of bits (digits) from max possible down to 2
        for (int m = 60; m >= 2; --m) {
            // Binary search range for the base k
            unsigned long long left = 2;
            unsigned long long right = n - 1;
            
            while (left <= right) {
                unsigned long long mid = left + (right - left) / 2;
                unsigned long long sum = 0;
                unsigned long long current_term = 1;
                bool overflow = false;
                
                // Calculate the geometric series sum: 1 + k + k^2 + ... + k^(m-1)
                for (int i = 0; i < m; ++i) {
                    sum += current_term;
                    if (i < m - 1) {
                        // Prevent overflow check before multiplying
                        if (current_term > n / mid) {
                            overflow = true;
                            break;
                        }
                        current_term *= mid;
                    }
                }
                
                if (overflow || sum > n) {
                    right = mid - 1; // Base is too large
                } else if (sum < n) {
                    left = mid + 1;  // Base is too small
                } else {
                    return std::to_string(mid); // Found the smallest good base
                }
            }
        }
        
        return std::to_string(n - 1);
    }
};
