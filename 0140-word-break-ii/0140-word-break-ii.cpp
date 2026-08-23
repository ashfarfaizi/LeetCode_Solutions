#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
private:
    // Hash map for memoization: stores the list of valid sentences formable from a suffix
    unordered_map<string, vector<string>> memo;

    vector<string> dfs(const string& s, const unordered_set<string>& wordSet) {
        // If this substring has already been processed, return the cached result
        if (memo.count(s)) {
            return memo[s];
        }
        
        // Base case: if the substring is empty, return a list containing an empty string
        if (s.empty()) {
            return {""};
        }

        vector<string> result;

        // Try splitting the string at every possible index
        for (int i = 1; i <= s.length(); ++i) {
            string prefix = s.substr(0, i);

            // If the prefix is a valid word, recursively solve for the remaining suffix
            if (wordSet.count(prefix)) {
                string suffix = s.substr(i);
                vector<string> suffixResult = dfs(suffix, wordSet);

                // Combine the current prefix with all valid sentences from the suffix
                for (const string& word : suffixResult) {
                    if (word.empty()) {
                        result.push_back(prefix);
                    } else {
                        result.push_back(prefix + " " + word);
                    }
                }
            }
        }

        // Cache the result for the current substring
        memo[s] = result;
        return result;
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        memo.clear();
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        return dfs(s, wordSet);
    }
};
