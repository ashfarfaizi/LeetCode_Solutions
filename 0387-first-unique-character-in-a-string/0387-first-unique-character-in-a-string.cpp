class Solution {
public:
    int firstUniqChar(string s) {
        // Since input consists only of lowercase letters, 
        // a fixed array of size 26 acts as a highly optimized hash map.
        int count[26] = {0};
        
        // Pass 1: Build the character frequency map
        for (char ch : s) {
            count[ch - 'a']++;
        }
        
        // Pass 2: Find the first character with a frequency of exactly 1
        for (int i = 0; i < s.length(); ++i) {
            if (count[s[i] - 'a'] == 1) {
                return i; // Return the index of the first unique character
            }
        }
        
        return -1; // Return -1 if no unique character exists
    }
};
