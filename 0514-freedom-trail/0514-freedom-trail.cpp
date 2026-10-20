class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int r_len = ring.length();
        int k_len = key.length();
        
        // Map each character in the ring to all its index locations
        unordered_map<char, vector<int>> char_positions;
        for (int i = 0; i < r_len; ++i) {
            char_positions[ring[i]].push_back(i);
        }
        
        // Memoization table initialized to -1
        vector<vector<int>> memo(k_len, vector<int>(r_len, -1));
        
        // Helper function for dynamic programming
        return solve(0, 0, ring, key, char_positions, memo);
    }

private:
    int solve(int k_idx, int r_idx, const string& ring, const string& key,
              unordered_map<char, vector<int>>& char_positions, vector<vector<int>>& memo) {
        
        // Base case: all characters in the key have been spelled
        if (k_idx == key.length()) {
            return 0;
        }
        
        // Return cached result if already calculated
        if (memo[k_idx][r_idx] != -1) {
            return memo[k_idx][r_idx];
        }
        
        int r_len = ring.length();
        int min_steps = INT_MAX;
        char target_char = key[k_idx];
        
        // Try matching with every possible position of the target character in the ring
        for (int next_r_idx : char_positions[target_char]) {
            // Calculate minimum steps to rotate (either clockwise or counter-clockwise)
            int steps_between = abs(r_idx - next_r_idx);
            int min_rotation = min(steps_between, r_len - steps_between);
            
            // 1 step is added to press the center button
            int total_steps = min_rotation + 1 + solve(k_idx + 1, next_r_idx, ring, key, char_positions, memo);
            
            min_steps = min(min_steps, total_steps);
        }
        
        return memo[k_idx][r_idx] = min_steps;
    }
};
