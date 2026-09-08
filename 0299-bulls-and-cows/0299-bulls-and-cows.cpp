#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string getHint(std::string secret, std::string guess) {
        int bulls = 0;
        int cows = 0;
        // Frequency array to keep track of unmatched digits (0-9)
        std::vector<int> counts(10, 0);
        
        for (int i = 0; i < secret.length(); ++i) {
            int sDigit = secret[i] - '0';
            int gDigit = guess[i] - '0';
            
            if (sDigit == gDigit) {
                bulls++;
            } else {
                // If sDigit has a negative count, it was previously requested by guess
                if (counts[sDigit] < 0) cows++;
                // If gDigit has a positive count, it was previously provided by secret
                if (counts[gDigit] > 0) cows++;
                
                // Track availability: secret increments, guess decrements
                counts[sDigit]++;
                counts[gDigit]--;
            }
        }
        
        return std::to_string(bulls) + "A" + std::to_string(cows) + "B";
    }
};
