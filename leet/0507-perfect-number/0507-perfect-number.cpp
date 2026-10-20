class Solution {
public:
    bool checkPerfectNumber(int num) {
        // Perfect numbers must be greater than 0. 1 is also not a perfect number 
        // because its only divisor is itself, and we must exclude the number itself.
        if (num <= 1) return false;
        
        int sum = 1; // 1 is always a proper divisor for any num > 1
        
        // Loop up to the square root of num
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                sum += i; // Add the divisor
                
                // If the divisors are distinct (e.g., avoid adding 6 twice for 36),
                // add the paired divisor (num / i)
                if (i * i != num) {
                    sum += num / i;
                }
            }
        }
        
        // Return true if the sum of proper divisors equals the original number
        return sum == num;
    }
};
