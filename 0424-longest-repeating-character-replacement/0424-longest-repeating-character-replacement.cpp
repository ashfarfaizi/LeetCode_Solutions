#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> counts(26, 0);
        int left = 0;
        int max_count = 0;
        int max_length = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // Update the count of the current character
            counts[s[right] - 'A']++;
            
            // Track the maximum frequency of a single character seen in the current window structure
            max_count = max(max_count, counts[s[right] - 'A']);
            
            // If the remaining characters to replace exceed k, shrink the window from the left
            if ((right - left + 1) - max_count > k) {
                counts[s[left] - 'A']--;
                left++;
            }
            
            // The window size at this point is always valid or matching our best historical size
            max_length = max(max_length, right - left + 1);
        }
        
        return max_length;
    }
};
