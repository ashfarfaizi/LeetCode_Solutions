#include <cmath>

class Solution {
public:
    int arrangeCoins(int n) {
        // Use 8.0 * n to force floating-point math and prevent integer overflow
        return (int)(-1.0 + std::sqrt(1.0 + 8.0 * n)) / 2;
    }
};
