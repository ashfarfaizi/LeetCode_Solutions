#include <string>
#include <algorithm>

class Solution {
public:
    std::string convertToBase7(int num) {
        // Edge case: if the number is 0, its base 7 representation is simply "0"
        if (num == 0) return "0";
        
        std::string result = "";
        bool isNegative = num < 0;
        
        // Work with absolute values to avoid negative modulo issues
        long long n = std::abs(static_cast<long long>(num));
        
        // Successive division method
        while (n > 0) {
            result += std::to_string(n % 7);
            n /= 7;
        }
        
        // Add negative sign if the original number was negative
        if (isNegative) {
            result += '-';
        }
        
        // The digits were added in reverse order, so flip the string
        std::reverse(result.begin(), result.end());
        
        return result;
    }
};
