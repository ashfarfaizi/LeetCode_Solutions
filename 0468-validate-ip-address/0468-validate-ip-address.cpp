#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

class Solution {
private:
    bool isValidIPv4(const string& queryIP) {
        // Edge cases: cannot start or end with a dot, nor have double dots
        if (queryIP.empty() || queryIP.front() == '.' || queryIP.back() == '.') return false;
        
        stringstream ss(queryIP);
        string segment;
        int count = 0;
        
        while (getline(ss, segment, '.')) {
            count++;
            if (count > 4 || segment.empty() || segment.length() > 3) return false;
            
            // Check for leading zeros
            if (segment.length() > 1 && segment[0] == '0') return false;
            
            // Ensure all characters are digits
            int num = 0;
            for (char c : segment) {
                if (!isdigit(c)) return false;
                num = num * 10 + (c - '0');
            }
            
            // Range check
            if (num < 0 || num > 255) return false;
        }
        
        return count == 4;
    }

    bool isValidIPv6(const string& queryIP) {
        // Edge cases: cannot start or end with a colon, nor have double colons
        if (queryIP.empty() || queryIP.front() == ':' || queryIP.back() == ':') return false;
        
        stringstream ss(queryIP);
        string segment;
        int count = 0;
        
        while (getline(ss, segment, ':')) {
            count++;
            if (count > 8 || segment.empty() || segment.length() > 4) return false;
            
            // Verify each character is a valid hex digit
            for (char c : segment) {
                if (!isxdigit(c)) return false;
            }
        }
        
        return count == 8;
    }

public:
    string validIPAddress(string queryIP) {
        // Quick dispatch based on string features
        if (queryIP.find('.') != string::npos) {
            return isValidIPv4(queryIP) ? "IPv4" : "Neither";
        } else if (queryIP.find(':') != string::npos) {
            return isValidIPv6(queryIP) ? "IPv6" : "Neither";
        }
        return "Neither";
    }
};
