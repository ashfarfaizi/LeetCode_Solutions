#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string originalDigits(string s) {
        // Track the frequencies of each character in the given string
        vector<int> char_counts(26, 0);
        for (char c : s) {
            char_counts[c - 'a']++;
        }
        
        // Track the final count of each digit from 0 to 9
        vector<int> digit_counts(10, 0);
        
        // Step 1: Identify numbers with entirely unique letters
        digit_counts[0] = char_counts['z' - 'a'];
        digit_counts[2] = char_counts['w' - 'a'];
        digit_counts[4] = char_counts['u' - 'a'];
        digit_counts[6] = char_counts['x' - 'a'];
        digit_counts[8] = char_counts['g' - 'a'];
        
        // Step 2: Identify numbers using unique overlaps
        digit_counts[3] = char_counts['h' - 'a'] - digit_counts[8]; // 'h' shared by 3 and 8
        digit_counts[5] = char_counts['f' - 'a'] - digit_counts[4]; // 'f' shared by 4 and 5
        digit_counts[7] = char_counts['s' - 'a'] - digit_counts[6]; // 's' shared by 6 and 7
        
        // Step 3: Clear out the remaining leftovers
        digit_counts[1] = char_counts['o' - 'a'] - digit_counts[0] - digit_counts[2] - digit_counts[4]; // 'o' shared by 0, 1, 2, 4
        digit_counts[9] = char_counts['i' - 'a'] - digit_counts[5] - digit_counts[6] - digit_counts[8]; // 'i' shared by 5, 6, 8, 9
        
        // Step 4: Reconstruct the string in ascending order
        string result = "";
        for (int i = 0; i <= 9; i++) {
            result.append(digit_counts[i], '0' + i);
        }
        
        return result;
    }
};
