#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }

public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> result;
        unordered_map<string, int> wordMap;
        
        // Step 1: Map each word to its original index for O(1) lookups
        for (int i = 0; i < words.size(); ++i) {
            wordMap[words[i]] = i;
        }
        
        // Step 2: Iterate through every word to find matching valid splits
        for (int i = 0; i < words.size(); ++i) {
            string word = words[i];
            int n = word.length();
            
            // j goes up to n inclusive to check both empty prefixes and empty suffixes
            for (int j = 0; j <= n; ++j) {
                // Case 1: Suffix is a palindrome
                if (isPalindrome(word, j, n - 1)) {
                    string prefix = word.substr(0, j);
                    reverse(prefix.begin(), prefix.end());
                    
                    // If the reversed prefix exists and is not the word itself
                    if (wordMap.count(prefix) && wordMap[prefix] != i) {
                        result.push_back({i, wordMap[prefix]});
                    }
                }
                
                // Case 2: Prefix is a palindrome 
                // (j > 0 prevents duplicate checks when j == 0)
                if (j > 0 && isPalindrome(word, 0, j - 1)) {
                    string suffix = word.substr(j);
                    reverse(suffix.begin(), suffix.end());
                    
                    // If the reversed suffix exists and is not the word itself
                    if (wordMap.count(suffix) && wordMap[suffix] != i) {
                        result.push_back({wordMap[suffix], i});
                    }
                }
            }
        }
        
        return result;
    }
};
