#include <cmath>

class Solution {
public:
    int integerBreak(int n) {
        // Base cases handled explicitly
        if (n == 2) return 1;
        if (n == 3) return 2;
        
        int remainder = n % 3;
        
        if (remainder == 0) {
            return pow(3, n / 3);
        } else if (remainder == 1) {
            return pow(3, (n / 3) - 1) * 4;
        } else { // remainder == 2
            return pow(3, n / 3) * 2;
        }
    }
};
