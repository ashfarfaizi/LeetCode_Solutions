#include <cmath>

class Solution {
public:
    int numSquares(int n) {
        // If n is already a perfect square, return 1
        int sqrt_n = std::sqrt(n);
        if (sqrt_n * sqrt_n == n) return 1;
        
        // Check if the answer is 4 using Legendre's theorem: n = 4^a * (8b + 7)
        while (n % 4 == 0) {
            n /= 4;
        }
        if (n % 8 == 7) return 4;
        
        // Check if the answer is 2 (n = i*i + j*j)
        for (int i = 1; i * i <= n; ++i) {
            int remaining = n - i * i;
            int sqrt_rem = std::sqrt(remaining);
            if (sqrt_rem * sqrt_rem == remaining) return 2;
        }
        
        // If it's not 1, 2, or 4, it must be 3
        return 3;
    }
};
