class Solution {
public:
    char findTheDifference(string s, string t) {
        char result = 0;
        
        // XOR all characters in string s
        for (char ch : s) {
            result ^= ch;
        }
        
        // XOR all characters in string t
        for (char ch : t) {
            result ^= ch;
        }
        
        return result;
    }
};
