#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        // Step 1: Reverse the entire string
        reverse(s.begin(), s.end());
        
        int n = s.length();
        int writeIdx = 0;
        
        for (int i = 0; i < n; ++i) {
            // Skip any spaces to find the beginning of a word
            if (s[i] != ' ') {
                // If this is not the first word being written, add a single spacing separator
                if (writeIdx != 0) {
                    s[writeIdx++] = ' ';
                }
                
                // Keep track of where the current word begins
                int wordStart = writeIdx;
                
                // Copy the word to its new compacted position
                while (i < n && s[i] != ' ') {
                    s[writeIdx++] = s[i++];
                }
                
                // Step 2: Reverse the letters of this individual word back to normal
                reverse(s.begin() + wordStart, s.begin() + writeIdx);
            }
        }
        
        // Step 3: Resize the string to chop off the trailing junk/spaces left behind
        s.erase(s.begin() + writeIdx, s.end());
        
        return s;
    }
};
