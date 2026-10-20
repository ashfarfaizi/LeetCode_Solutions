class Solution {
public:
    int fib(int n) {
        // Base cases
        if (n == 0) return 0;
        if (n == 1) return 1;
        
        // Variables to keep track of the last two Fibonacci numbers
        int prev2 = 0; // F(n-2)
        int prev1 = 1; // F(n-1)
        int current = 0;
        
        // Iteratively compute Fibonacci numbers up to n
        for (int i = 2; i <= n; ++i) {
            current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        
        return current;
    }
};
