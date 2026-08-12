#include <string>
#include <vector>

class Solution {
public:
    std::vector<std::string> restoreIpAddresses(std::string s) {
        std::vector<std::string> result;
        std::string currentIp;
        
        // An IP address has exactly 4 segments and a max length of 12 characters (3 digits per segment)
        if (s.length() < 4 || s.length() > 12) {
            return result;
        }
        
        backtrack(s, 0, 0, currentIp, result);
        return result;
    }

private:
    void backtrack(const std::string& s, int startIndex, int segmentCount, std::string currentIp, std::vector<std::string>& result) {
        // If we have parsed all 4 segments
        if (segmentCount == 4) {
            // If we also consumed the entire input string, it's a valid configuration
            if (startIndex == s.length()) {
                // Remove the trailing dot before adding to results
                currentIp.pop_back();
                result.push_back(currentIp);
            }
            return;
        }
        
        // If we reached the end of the string but haven't formed 4 segments yet, terminate early
        if (startIndex == s.length()) {
            return;
        }
        
        // Each segment can be 1, 2, or 3 digits long
        for (int len = 1; len <= 3; ++len) {
            // Prevent out of bounds slicing
            if (startIndex + len > s.length()) {
                break;
            }
            
            std::string part = s.substr(startIndex, len);
            int value = std::stoi(part);
            
            // Check for valid segment constraints:
            // 1. Value must be between 0 and 255
            // 2. No leading zeros (e.g., "01" or "015" are invalid, but a single "0" is valid)
            if (value > 255 || (len > 1 && part[0] == '0')) {
                break;
            }
            
            // Recursively process the next segment
            backtrack(s, startIndex + len, segmentCount + 1, currentIp + part + ".", result);
        }
    }
};
