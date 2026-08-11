#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_map<string, bool> memo;

public:
    bool isScramble(string s1, string s2) {
        // Base case: if strings are identical, they are scrambles of each other
        if (s1 == s2) return true;
        
        int len = s1.length();
        
        // Pruning: Anagram check using a local frequency array
        vector<int> count(26, 0);
        for (int i = 0; i < len; ++i) {
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
        }
        for (int i = 0; i < 26; ++i) {
            if (count[i] != 0) return false;
        }

        // Memoization lookup key
        string key = s1 + "#" + s2;
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }

        // Try all possible split positions
        for (int i = 1; i < len; ++i) {
            // Case 1: Substrings are NOT swapped
            // s1_left vs s2_left AND s1_right vs s2_right
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) && 
                isScramble(s1.substr(i), s2.substr(i))) {
                return memo[key] = true;
            }

            // Case 2: Substrings ARE swapped
            // s1_left vs s2_right AND s1_right vs s2_left
            if (isScramble(s1.substr(0, i), s2.substr(len - i)) && 
                isScramble(s1.substr(i), s2.substr(0, len - i))) {
                return memo[key] = true;
            }
        }

        return memo[key] = false;
    }
};
