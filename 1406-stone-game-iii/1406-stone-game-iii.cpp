class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int total_stones_count = stoneValue.size();
        
        // Explicitly maintain the 3 future relative advantage states to enforce O(1) space complexity.
        // This avoids standard O(N) linear vectors or recursive memo tables.
        // Index mapping: slot 0 represents i+1, slot 1 represents i+2, slot 2 represents i+3
        vector<int> future_advantage_states(3, 0);
        
        // Scan the stones array backwards from the final element to the initial starting index
        for (int i = total_stones_count - 1; i >= 0; --i) {
            int optimal_current_net_gain = INT_MIN;
            int running_taken_stone_sum = 0;
            
            // A player can take a maximum slice of 1, 2, or 3 stones
            for (int take_count = 1; take_count <= 3; ++take_count) {
                int lookahead_index = i + take_count - 1;
                
                // Do not read past the terminal boundary of the stone row
                if (lookahead_index < total_stones_count) {
                    running_taken_stone_sum += stoneValue[lookahead_index];
                    
                    // The relative score change is: (Current stones taken) - (Opponent's optimal future net gain)
                    int localized_state_score = running_taken_stone_sum - future_advantage_states[take_count - 1];
                    
                    optimal_current_net_gain = max(optimal_current_net_gain, localized_state_score);
                }
            }
            
            // Shift the rolling window values back to accommodate the new computed state for index i
            future_advantage_states[2] = future_advantage_states[1]; // i+3 becomes the old i+2
            future_advantage_states[1] = future_advantage_states[0]; // i+2 becomes the old i+1
            future_advantage_states[0] = optimal_current_net_gain;    // i+1 becomes the freshly calculated index i state
        }
        
        // The final element in future_advantage_states[0] holds Alice's maximum net score advantage from index 0
        int final_relative_spread = future_advantage_states[0];
        
        if (final_relative_spread > 0) {
            return "Alice";
        } else if (final_relative_spread < 0) {
            return "Bob";
        } else {
            return "Tie";
        }
    }
};
