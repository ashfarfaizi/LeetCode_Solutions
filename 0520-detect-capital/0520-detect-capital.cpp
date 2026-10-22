#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    bool detectCapitalUse(string word) {
        int capitals = 0;
        for (char c : word) {
            if (isupper(c)) {
                capitals++;
            }
        }
        
        if (capitals == word.length() || capitals == 0) {
            return true;
        }
        
        return capitals == 1 && isupper(word[0]);
    }
};
