class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_ptr = 0;
        int t_ptr = 0;
        
        // Scan through both strings
        while (s_ptr < s.length() && t_ptr < t.length()) {
            if (s[s_ptr] == t[t_ptr]) {
                s_ptr++; // Move s pointer only when characters match
            }
            t_ptr++; // Always move t pointer
        }
        
        // If s_ptr reached the end of s, then s is a subsequence
        return s_ptr == s.length();
    }
};
