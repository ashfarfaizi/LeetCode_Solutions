class Solution {
public:
    bool isMatch(string s, string p) {
        int s_len = s.length();
        int p_len = p.length();
        
        // State tracker: active_pattern_states[j] is true if the prefix p[0...j-1] 
        // matches the currently consumed prefix of string s.
        // We use a flat vector of bools acting as a manual bitset machine.
        vector<bool> active_pattern_states(p_len + 1, false);
        
        // Base Condition: Before consuming any characters from s, an empty s matches an empty p
        active_pattern_states[0] = true;
        
        // Propagate the initial active state through any leading '*' tokens in the pattern
        for (int j = 1; j <= p_len; ++j) {
            if (p[j - 1] == '*') {
                active_pattern_states[j] = active_pattern_states[j - 1];
            } else {
                break;
            }
        }
        
        // Main Execution Engine: Consume the characters of string s one-by-one
        for (int i = 1; i <= s_len; ++i) {
            char current_s_char = s[i - 1];
            
            // This will hold the valid pattern configurations for the current character round
            vector<bool> next_pattern_states(p_len + 1, false);
            
            // Evaluate standard transition paths across the pattern elements
            for (int j = 1; j <= p_len; ++j) {
                char current_p_char = p[j - 1];
                
                if (current_p_char == '*') {
                    // '*' can match an empty sequence (inheriting the state directly from the left)
                    // or match the current character (inheriting its own previous state from the prior round)
                    next_pattern_states[j] = next_pattern_states[j - 1] || active_pattern_states[j];
                } else if (current_p_char == '?' || current_p_char == current_s_char) {
                    // Match successful: propagate the previous round's state forward diagonal-style
                    next_pattern_states[j] = active_pattern_states[j - 1];
                }
            }
            
            // Broadcast wave propagation: A '*' element extends its active state to the right
            // because it can absorb any sequence of characters within this round.
            for (int j = 1; j <= p_len; ++j) {
                if (p[j - 1] == '*' && next_pattern_states[j - 1]) {
                    next_pattern_states[j] = true;
                }
            }
            
            // Move the freshly computed layer forward to replace the older state machine generation
            active_pattern_states = std::move(next_pattern_states);
        }
        
        // The final element signifies whether the entire pattern string p safely digested string s
        return active_pattern_states[p_len];
    }
};
