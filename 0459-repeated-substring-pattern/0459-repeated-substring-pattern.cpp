class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        // Double the string
        string doubled = s + s;
        
        // Remove the first and last characters
        string total = doubled.substr(1, doubled.length() - 2);
        
        // Check if the original string exists in the modified doubled string
        return total.find(s) != string::npos;
    }
};
