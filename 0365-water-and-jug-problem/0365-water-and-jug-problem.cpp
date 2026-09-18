#include <numeric>

class Solution {
public:
    bool canMeasureWater(int x, int y, int target) {
        // Condition 1: Target cannot be more than the total capacity
        if (x + y < target) {
            return false;
        }
        
        // Condition 2: Target must be a multiple of the GCD of x and y
        // std::gcd requires the <numeric> header (C++17 onwards)
        return target % std::gcd(x, y) == 0;
    }
};
