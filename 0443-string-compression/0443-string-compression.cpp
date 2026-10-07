#include <vector>
#include <string>

class Solution {
public:
    int compress(std::vector<char>& chars) {
        int write = 0; // Pointer to overwrite elements in-place
        int i = 0;     // Pointer to read elements
        int n = chars.size();
        
        while (i < n) {
            char currChar = chars[i];
            int count = 0;
            
            // Count the consecutive repeating characters
            while (i < n && chars[i] == currChar) {
                count++;
                i++;
            }
            
            // Write the character itself
            chars[write++] = currChar;
            
            // If the group's length is greater than 1, write its count
            if (count > 1) {
                std::string countStr = std::to_string(count);
                for (char c : countStr) {
                    chars[write++] = c;
                }
            }
        }
        
        return write; // The new length of the compressed array
    }
};
