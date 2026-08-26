#include <string>
#include <algorithm>

class Solution {
public:
    std::string convertToTitle(int columnNumber) {
        std::string result = "";
        
        while (columnNumber > 0) {
            // Shift to 0-indexed system (0 = A, 25 = Z)
            columnNumber--;
            
            // Extract the current character
            char current_char = 'A' + (columnNumber % 26);
            result += current_char;
            
            // Move to the next higher place value
            columnNumber /= 26;
        }
        
        // The characters were collected from right to left, so reverse them
        std::reverse(result.begin(), result.end());
        return result;
    }
};
