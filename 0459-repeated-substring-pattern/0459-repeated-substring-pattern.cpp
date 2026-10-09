#include <string>

class Solution {
public:
    bool repeatedSubstringPattern(std::string s) {
        // Double the string
        std::string doubled = s + s;
        
        // Remove the first and last characters to clear the original boundaries
        std::string total = doubled.substr(1, doubled.length() - 2);
        
        // If s can be formed by repeating a substring, it must exist inside the middle
        return total.find(s) != std::string::npos;
    }
};
