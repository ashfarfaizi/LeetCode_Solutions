#include <cmath>

class Solution {
public:
    int bulbSwitch(int n) {
        // The number of bulbs left on is the count of perfect squares <= n.
        return std::sqrt(n);
    }
};
