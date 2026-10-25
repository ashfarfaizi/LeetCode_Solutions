class Solution {
public:
    string reverseWords(string s) {
        int n = s.length();
        int start = 0;
        
        for (int i = 0; i <= n; ++i) {
            // Reverse when we reach a space or the end of the string
            if (i == n || s[i] == ' ') {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1; // Move the start pointer to the beginning of the next word
            }
        }
        
        return s;
    }
};
