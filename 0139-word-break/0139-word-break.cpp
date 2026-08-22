class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // Convert dictionary to an unordered_set for O(1) lookups
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        
        int n = s.length();
        // dp[i] stores whether s[0...i-1] can be segmented
        vector<bool> dp(n + 1, false);
        
        // Base case: empty string is valid
        dp[0] = true;
        
        // Iterate through all lengths of the substring
        for (int i = 1; i <= n; i++) {
            // Check all possible split points trailing behind index i
            for (int j = 0; j < i; j++) {
                // If prefix s[0...j-1] is valid and s[j...i-1] is in dictionary
                if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break; // Found a valid segmentation for length i, move to next i
                }
            }
        }
        
        return dp[n];
    }
};
