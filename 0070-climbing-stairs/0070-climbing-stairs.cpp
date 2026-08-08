#include <iostream>

class Solution {
public:
    int climbStairs(int n) {
        // Base cases: 1 way for 1 step, 2 ways for 2 steps
        if (n == 1) return 1;
        if (n == 2) return 2;

        // Variables representing ways to reach the previous two stairs
        int step_minus_two = 1; // f(1)
        int step_minus_one = 2; // f(2)
        int current_ways = 0;   // f(n)

        // Iteratively compute combinations using the rolling window approach
        for (int i = 3; i <= n; ++i) {
            current_ways = step_minus_one + step_minus_two;
            
            // Shift the window forward for the next iteration
            step_minus_two = step_minus_one;
            step_minus_one = current_ways;
        }

        return current_ways;
    }
};
