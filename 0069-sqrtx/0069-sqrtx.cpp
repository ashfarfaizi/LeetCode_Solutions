#include <iostream>

class Solution {
public:
    int mySqrt(int x) {
        // Base cases for 0 and 1
        if (x == 0 || x == 1) {
            return x;
        }

        int low = 1;
        int high = x;
        int result = 0;

        while (low <= high) {
            // Prevent potential integer overflow when calculating mid
            int mid = low + (high - low) / 2;

            // Equivalent to: mid * mid <= x (restructured to eliminate overflow)
            if (mid <= x / mid) {
                result = mid;     // Track the best integer floor value seen so far
                low = mid + 1;    // Try to find a larger matching integer floor
            } else {
                high = mid - 1;   // The value is too large, narrow down upper bound
            }
        }

        return result;
    }
};
