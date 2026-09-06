class Solution {
public:
    bool isUgly(int n) {
        // Base case: Any number less than or equal to 0 cannot be an ugly number
        if (n <= 0) return false;
        
        // Repeatedly divide by the allowed prime factors
        while (n % 2 == 0) n /= 2;
        while (n % 3 == 0) n /= 3;
        while (n % 5 == 0) n /= 5;
        
        // If the number reduces down to 1, then it only had 2, 3, or 5 as prime factors
        return n == 1;
    }
};
