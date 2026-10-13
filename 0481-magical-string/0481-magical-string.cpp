#include <string>

class Solution {
public:
    int magicalString(int n) {
        if (n <= 0) return 0;
        if (n <= 3) return 1; // For n=1, 2, or 3, the prefix "122" contains exactly one '1'

        // Start with the known base sequence
        std::string s = "122";
        int i = 2; // Pointer to read the group size count

        // Construct the string until it has at least n elements
        while (s.length() < n) {
            // Determine the next character to append (toggle between '1' and '2')
            char next_char = (s.back() == '1') ? '2' : '1';
            
            // Determine how many times to repeat it based on s[i]
            int count = s[i] - '0';
            
            // Append the character 'count' times
            s.append(count, next_char);
            
            // Move forward to read the next group size
            i++;
        }

        // Count the number of '1's in the first n characters
        int one_count = 0;
        for (int k = 0; k < n; ++k) {
            if (s[k] == '1') {
                one_count++;
            }
        }

        return one_count;
    }
};
