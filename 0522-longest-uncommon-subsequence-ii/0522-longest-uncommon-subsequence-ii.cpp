#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool isSubsequence(const string& s1, const string& s2) {
        int i = 0, j = 0;
        while (i < s1.length() && j < s2.length()) {
            if (s1[i] == s2[j]) {
                i++;
            }
            j++;
        }
        return i == s1.length();
    }

public:
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
            return a.length() > b.length();
        });
        
        int n = strs.size();
        for (int i = 0; i < n; i++) {
            bool is_uncommon = true;
            for (int j = 0; j < n; j++) {
                if (i != j && isSubsequence(strs[i], strs[j])) {
                    is_uncommon = false;
                    break;
                }
            }
            if (is_uncommon) {
                return strs[i].length();
            }
        }
        
        return -1;
    }
};
