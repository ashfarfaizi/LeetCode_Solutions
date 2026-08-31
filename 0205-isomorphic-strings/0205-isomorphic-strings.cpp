#include <string>
#include <vector>

class Solution {
public:
    bool isIsomorphic(std::string s, std::string t) {
        // Since input consists of valid ASCII characters, a size of 256 is sufficient
        // Initialize with 0 representing that the character hasn't been seen yet
        int mapS[256] = {0};
        int mapT[256] = {0};
        
        int len = s.length();
        
        for (int i = 0; i < len; ++i) {
            // If the previous position records do not match, the structures conflict
            if (mapS[static_cast<unsigned char>(s[i])] != mapT[static_cast<unsigned char>(t[i])]) {
                return false;
            }
            
            // Record the current structural group position index (1-based to distinguish from 0)
            mapS[static_cast<unsigned char>(s[i])] = i + 1;
            mapT[static_cast<unsigned char>(t[i])] = i + 1;
        }
        
        return true;
    }
};
