#include <string>
#include <vector>

class Solution {
public:
    std::string removeDuplicateLetters(std::string s) {
        std::vector<int> last_idx(26, 0);
        std::vector<bool> seen(26, false);
        std::string result = ""; // Acting as our stack
        
        // Find the last occurrence index of each character
        for (int i = 0; i < s.length(); ++i) {
            last_idx[s[i] - 'a'] = i;
        }
        
        for (int i = 0; i < s.length(); ++i) {
            int curr = s[i] - 'a';
            
            // If character is already in our result stack, skip it
            if (seen[curr]) continue;
            
            // Maintain monotonic property: pop larger characters if they appear later
            while (!result.empty() && result.back() > s[i] && last_idx[result.back() - 'a'] > i) {
                seen[result.back() - 'a'] = false;
                result.pop_back();
            }
            
            // Push current character
            result.push_back(s[i]);
            seen[curr] = true;
        }
        
        return result;
    }
};
