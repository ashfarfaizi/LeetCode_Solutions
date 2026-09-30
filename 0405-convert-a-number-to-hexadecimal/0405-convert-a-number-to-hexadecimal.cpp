#include <string>
#include <algorithm>

class Solution {
public:
    string toHex(int num) {
        if (num == 0) return "0";
        
        // Treating 'num' as unsigned handles 32-bit two's complement automatically
        unsigned int n = num; 
        string hex_digits = "0123456789abcdef";
        string result = "";
        
        while (n > 0) {
            // Get the last 4 bits
            int rem = n & 15; 
            result += hex_digits[rem];
            // Shift right by 4 bits
            n >>= 4; 
        }
        
        // Reverse because we extracted from right to left
        reverse(result.begin(), result.end());
        return result;
    }
};
