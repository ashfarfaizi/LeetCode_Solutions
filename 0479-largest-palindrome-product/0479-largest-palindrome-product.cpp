class Solution {
public:
    int largestPalindrome(int n) {
        // Base case for single digit
        if (n == 1) return 9;
        
        // Calculate upper and lower bounds for n-digit numbers
        long long upper_bound = pow(10, n) - 1;
        long long lower_bound = pow(10, n - 1);
        
        // Iterate through the upper halves in descending order
        for (long long i = upper_bound; i >= lower_bound; --i) {
            // Generate the palindrome from its upper half
            long long palindrome = i;
            long long temp = i;
            while (temp > 0) {
                palindrome = palindrome * 10 + (temp % 10);
                temp /= 10;
            }
            
            // Check if this palindrome can be factored into two n-digit numbers
            for (long long j = upper_bound; j * j >= palindrome; --j) {
                if (palindrome % j == 0) {
                    return palindrome % 1337;
                }
            }
        }
        
        return 0;
    }
};
