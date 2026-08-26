#include <string>

class Solution {
public:
    int titleToNumber(std::string columnTitle) {
        int result = 0;
        
        for (char c : columnTitle) {
            // Calculate value of current character (A -> 1, B -> 2, ..., Z -> 26)
            int current_value = c - 'A' + 1;
            
            // Shift existing positions by base 26 and add current character value
            // Using standard type matching as the maximum result safely fits in an int
            result = result * 26 + current_value;
        }
        
        return result;
    }
};
