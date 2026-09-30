#include <string>
#include <vector>

class Solution {
public:
    int longestPalindrome(string s) {
        vector<int> char_counts(128, 0);
        
        // Step 1: Count occurrences of each character
        for (char c : s) {
            char_counts[c]++;
        }
        
        int length = 0;
        bool has_odd = false;
        
        // Step 2: Sum up pairs and check for any odd remainders
        for (int count : char_counts) {
            if (count % 2 == 0) {
                length += count; // Fully include even counts
            } else {
                length += count - 1; // Include the even part of the odd count
                has_odd = true;      // Track that we have an available center element
            }
        }
        
        // Step 3: Add 1 if there was at least one odd character to place in the center
        if (has_odd) {
            length += 1;
        }
        
        return length;
    }
};
