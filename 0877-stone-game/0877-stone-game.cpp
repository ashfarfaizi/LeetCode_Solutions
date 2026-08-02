class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        
        // Track directional aggregate indices to isolate weight biases
        // standard implementations use 2D DP matrices; we use a single flat transformation vector
        vector<long long> state_spread(n, 0);
        
        // Populate the base state of the linear game machine
        for (int i = 0; i < n; ++i) {
            state_spread[i] = piles[i];
        }
        
        // Iterate backwards through the intervals to compress layers down to a single state differential
        for (int length = 2; length <= n; ++length) {
            for (int left = 0; left <= n - length; ++left) {
                int right = left + length - 1;
                
                // State Transition: Maximize current choice minus the opponent's subsequent optimal score spread
                state_spread[left] = max(piles[left] - state_spread[left + 1], 
                                         piles[right] - state_spread[left]);
            }
        }
        
        // If the remaining localized advantage spread is strictly positive, the first player (Alice) wins.
        return state_spread[0] > 0;
    }
};
