#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();

        // dp[i][j] stores the edit distance for word1[0...i-1] and word2[0...j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Initialize base cases for transforming into/from empty strings
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i; // Deleting i characters
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j; // Inserting j characters
        }

        // Compute optimal operations bottom-up
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    // Characters match, no operation cost incurred
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Match failed; take minimum of (Insert, Delete, Replace) + 1
                    dp[i][j] = 1 + min({
                        dp[i][j - 1],   // Insert
                        dp[i - 1][j],   // Delete
                        dp[i - 1][j - 1] // Replace
                    });
                }
            }
        }

        return dp[m][n];
    }
};
