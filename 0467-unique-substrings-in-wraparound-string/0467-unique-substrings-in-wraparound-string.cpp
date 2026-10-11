#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findSubstringInWraproundString(string s) {
        if (s.empty()) return 0;
        
        // max_len[i] will store the maximum length of a valid substring ending with character ('a' + i)
        vector<int> max_len(26, 0);
        
        int current_continuous_len = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            // Check if the current character continues the wraparound pattern from the previous one
            if (i > 0 && (s[i] - s[i - 1] == 1 || s[i - 1] - s[i] == 25)) {
                current_continuous_len++;
            } else {
                current_continuous_len = 1; // Reset to 1 if the pattern breaks
            }
            
            // Map character to an alphabet index (0-25)
            int char_idx = s[i] - 'a';
            
            // Update the maximum length found so far ending at this character
            max_len[char_idx] = max(max_len[char_idx], current_continuous_len);
        }
        
        // Sum up all unique substring counts stored in the history vector
        return accumulate(max_len.begin(), max_len.end(), 0);
    }
};
