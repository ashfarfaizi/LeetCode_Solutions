#include <vector>

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;
        
        // Use vector<char> instead of vector<bool> to avoid bit-packing overhead
        std::vector<char> isPrime(n, 1); 
        
        // Start by assuming all numbers from 2 to n-1 are prime
        int primeCount = n - 2; 
        
        for (int i = 2; i * i < n; i++) {
            if (isPrime[i]) {
                // Eliminate composite multiples
                for (int j = i * i; j < n; j += i) {
                    if (isPrime[j]) {
                        isPrime[j] = 0; // Mark as composite
                        primeCount--;   // Decrement the count on the fly
                    }
                }
            }
        }
        
        return primeCount;
    }
};
