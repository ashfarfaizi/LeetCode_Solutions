#include <string>

using namespace std;

class Solution {
public:
    int countSegments(string s) {
        int segmentsCount = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            // Check if the current character starts a new segment
            if (s[i] != ' ' && (i == 0 || s[i - 1] == ' ')) {
                segmentsCount++;
            }
        }
        
        return segmentsCount;
    }
};
