#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        
        // last_match[j] will store the maximum index in word1 from which 
        // the suffix word2[j...m-1] can be fully matched without any mismatch modifications.
        vector<int> last_match(m, -1);
        
        int j = m - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (j >= 0 && word1[i] == word2[j]) {
                last_match[j] = i;
                j--;
            }
        }
        
        vector<int> result;
        int word1_idx = 0;
        bool mismatch_used = false;
        
        for (int word2_idx = 0; word2_idx < m; ++word2_idx) {
            // Find the first index in word1 that can fulfill the condition
            while (word1_idx < n) {
                // Scenario 1: The characters match perfectly
                if (word1[word1_idx] == word2[word2_idx]) {
                    result.push_back(word1_idx);
                    word1_idx++;
                    break;
                }
                
                // Scenario 2: The characters do not match, but we have our 1-character modification strategy left
                if (!mismatch_used) {
                    // Check if the remaining suffix of word2 can be safely formed 
                    // from the remainder of word1 without any further mismatches.
                    bool suffix_match_possible = (word2_idx + 1 == m) || 
                                                 ((word1_idx + 1 < n) && (word1_idx + 1 <= last_match[word2_idx + 1]));
                    
                    if (suffix_match_possible) {
                        mismatch_used = true;
                        result.push_back(word1_idx);
                        word1_idx++;
                        break;
                    }
                }
                
                // If it can't match or be modified, skip this character in word1
                word1_idx++;
            }
            
            // If we ran out of word1 characters before filling the result sequence, no valid configuration exists
            if (result.size() <= word2_idx) {
                return {};
            }
        }
        
        return result;
    }
};
