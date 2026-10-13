#include <string>
#include <algorithm>
#include <cctype>

class Solution {
public:
    std::string licenseKeyFormatting(std::string s, int k) {
        std::string result = "";
        int char_count = 0;

        // Traverse the string from back to front
        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] != '-') {
                // If we already filled a group of size k, insert a dash before the next char
                if (char_count > 0 && char_count % k == 0) {
                    result.push_back('-');
                }
                
                // Add the uppercase alphanumeric character
                result.push_back(toupper(s[i]));
                char_count++;
            }
        }

        // Reverse the result string since we built it backwards
        std::reverse(result.begin(), result.end());
        return result;
    }
};
