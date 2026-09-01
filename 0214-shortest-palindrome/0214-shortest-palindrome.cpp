#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string shortestPalindrome(std::string s) {
        if (s.empty()) return s;
        
        std::string rev_s = s;
        std::reverse(rev_s.begin(), rev_s.end());
        
        // Combine string with a separator to calculate matching prefix boundaries
        std::string combined = s + "#" + rev_s;
        int n = combined.length();
        
        // Build KMP LPS (Longest Prefix Suffix) table
        std::vector<int> lps(n, 0);
        for (int i = 1; i < n; ++i) {
            int j = lps[i - 1];
            
            while (j > 0 && combined[i] != combined[j]) {
                j = lps[j - 1];
            }
            
            if (combined[i] == combined[j]) {
                j++;
            }
            lps[i] = j;
        }
        
        // lps.back() contains the length of the longest palindromic prefix
        int longest_palindrome_prefix_len = lps.back();
        
        // Take the un-matched suffix from the end of s
        std::string suffix_to_add = s.substr(longest_palindrome_prefix_len);
        
        // Reverse it to put it in front
        std::reverse(suffix_to_add.begin(), suffix_to_add.end());
        
        return suffix_to_add + s;
    }
};
