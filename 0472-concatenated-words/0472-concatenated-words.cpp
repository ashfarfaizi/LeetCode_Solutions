#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool isConcatenated(const string& word, const unordered_set<string>& dict) {
        if (dict.empty()) return false;
        int n = word.length();
        // dp[i] indicates if the prefix word[0...i-1] can be formed by words in the dict
        vector<bool> dp(n + 1, false);
        dp[0] = true; // Base case: empty string
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                // If prefix word[0...j-1] is valid and word[j...i-1] exists in dict
                if (dp[j] && dict.count(word.substr(j, i - j))) {
                    dp[i] = true;
                    break; // Found a valid breakdown for prefix length i
                }
            }
        }
        return dp[n];
    }

public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        // Sort words by length: shorter words are processed first
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.length() < b.length();
        });
        
        unordered_set<string> dict;
        vector<string> result;
        
        for (const string& word : words) {
            if (isConcatenated(word, dict)) {
                result.push_back(word);
            }
            // Always insert the current word into the dictionary for future longer words
            dict.insert(word);
        }
        
        return result;
    }
};
