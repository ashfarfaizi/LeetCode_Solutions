#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    int n;
    // dp[i][M] stores the max stones Alice can get starting at index i with current M
    vector<vector<int>> memo;
    // suffix_sums[i] stores the total stones available from index i to the end
    vector<int> suffix_sums;

    int solve(int i, int M, const vector<int>& piles) {
        // If we can take all the remaining piles, take them all greedily
        if (i + 2 * M >= n) {
            return suffix_sums[i];
        }
        
        // Return cached result if already calculated
        if (memo[i][M] != -1) {
            return memo[i][M];
        }

        int opponent_best = 1e9; // Minimize the stones the next player can get

        // Try taking X piles where 1 <= X <= 2 * M
        for (int X = 1; X <= 2 * M; ++X) {
            opponent_best = min(opponent_best, solve(i + X, max(M, X), piles));
        }

        // Alice gets all remaining stones minus the best stones Bob can collect
        return memo[i][M] = suffix_sums[i] - opponent_best;
    }

public:
    int stoneGameII(vector<int>& piles) {
        n = piles.size();
        memo.assign(n, vector<int>(n + 1, -1));
        suffix_sums.assign(n + 1, 0);

        // Precompute suffix sums to find remaining stones instantly
        for (int i = n - 1; i >= 0; --i) {
            suffix_sums[i] = suffix_sums[i + 1] + piles[i];
        }

        // Game starts at pile 0 with M = 1
        return solve(0, 1, piles);
    }
};
