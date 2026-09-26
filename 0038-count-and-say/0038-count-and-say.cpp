#include <string>

class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) return "1";
        
        string current = "1";
        
        // Generate the sequence iteratively up to n
        for (int i = 2; i <= n; ++i) {
            string next_seq = "";
            int len = current.length();
            
            int count = 1;
            for (int j = 1; j < len; ++j) {
                if (current[j] == current[j - 1]) {
                    count++; // Increment count for identical consecutive characters
                } else {
                    // Append the count followed by the digit character
                    next_seq += to_string(count) + current[j - 1];
                    count = 1; // Reset count for the new character group
                }
            }
            // Append the last remaining group
            next_seq += to_string(count) + current[len - 1];
            current = next_seq; // Update the current sequence for the next iteration
        }
        
        return current;
    }
};
