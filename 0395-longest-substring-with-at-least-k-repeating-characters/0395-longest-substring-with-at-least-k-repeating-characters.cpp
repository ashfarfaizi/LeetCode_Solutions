#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestSubstring(std::string s, int k) {
        int n = s.length();
        if (n == 0 || k > n) return 0;
        if (k <= 1) return n;
        
        // Count frequencies of all characters in the current substring
        std::vector<int> counts(26, 0);
        for (char ch : s) {
            counts[ch - 'a']++;
        }
        
        // Find the first character that breaks the frequency requirement
        int split_idx = 0;
        while (split_idx < n && counts[s[split_idx] - 'a'] >= k) {
            split_idx++;
        }
        
        // If all characters satisfy the condition, the whole string is valid
        if (split_idx == n) return n;
        
        // The split character cannot be part of the valid substring. 
        // Solve recursively for the left half
        int left_res = longestSubstring(s.substr(0, split_idx), k);
        
        // Skip over any consecutive invalid characters to optimize performance
        while (split_idx < n && counts[s[split_idx] - 'a'] < k) {
            split_idx++;
        }
        
        // Solve recursively for the remaining right half
        int right_res = (split_idx < n) ? longestSubstring(s.substr(split_idx), k) : 0;
        
        return std::max(left_res, right_res);
    }
};
