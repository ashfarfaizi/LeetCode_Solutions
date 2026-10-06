#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        int sLen = s.length();
        int pLen = p.length();
        
        // If s is shorter than p, it cannot contain an anagram
        if (sLen < pLen) return result;
        
        // Frequency arrays for characters 'a' through 'z'
        vector<int> pCount(26, 0);
        vector<int> sCount(26, 0);
        
        // Initialize the count for string p and the first window of s
        for (int i = 0; i < pLen; ++i) {
            pCount[p[i] - 'a']++;
            sCount[s[i] - 'a']++;
        }
        
        // Check the first window
        if (sCount == pCount) {
            result.push_back(0);
        }
        
        // Slide the window across string s
        for (int i = pLen; i < sLen; ++i) {
            // Add the new character entering the window from the right
            sCount[s[i] - 'a']++;
            
            // Remove the character leaving the window from the left
            sCount[s[i - pLen] - 'a']--;
            
            // Compare the frequency tracking arrays
            if (sCount == pCount) {
                result.push_back(i - pLen + 1);
            }
        }
        
        return result;
    }
};
