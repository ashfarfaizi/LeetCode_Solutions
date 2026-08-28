#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        // If the string length is less than 10, no 10-letter sequence can repeat
        if (s.length() < 10) {
            return {};
        }
        
        unordered_set<string> seen;
        unordered_set<string> repeated;
        
        // Slide a window of size 10 across the string
        for (int i = 0; i <= s.length() - 10; ++i) {
            string current = s.substr(i, 10);
            
            // If we've seen this substring before, add it to our repeated set
            if (seen.count(current)) {
                repeated.insert(current);
            } else {
                // Otherwise, mark it as seen
                seen.insert(current);
            }
        }
        
        // Convert the repeated set into the final output vector
        return vector<string>(repeated.begin(), repeated.end());
    }
};
