class Solution {
public:
    int longestValidParentheses(string s) {
        int maximum_valid_span = 0;
        
        int open_brackets_count = 0;
        int close_brackets_count = 0;
        
        // Phase 1: Forward geometric tracking sweep
        for (char bracket_token : s) {
            if (bracket_token == '(') {
                open_brackets_count++;
            } else {
                close_brackets_count++;
            }
            
            // A perfect balance signifies a well-formed substring boundary
            if (open_brackets_count == close_brackets_count) {
                maximum_valid_span = max(maximum_valid_span, 2 * close_brackets_count);
            } 
            // In the forward pass, an excess of closing tokens invalidates the current sequence
            else if (close_brackets_count > open_brackets_count) {
                open_brackets_count = 0;
                close_brackets_count = 0;
            }
        }
        
        // Reset coordinate state vectors for the reverse pass
        open_brackets_count = 0;
        close_brackets_count = 0;
        
        // Phase 2: Backward geometric tracking sweep to catch trailing open-bracket remnants
        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] == '(') {
                open_brackets_count++;
            } else {
                close_brackets_count++;
            }
            
            if (open_brackets_count == close_brackets_count) {
                maximum_valid_span = max(maximum_valid_span, 2 * open_brackets_count);
            } 
            // In the backward pass, an excess of opening tokens invalidates the current sequence
            else if (open_brackets_count > close_brackets_count) {
                open_brackets_count = 0;
                close_brackets_count = 0;
            }
        }
        
        return maximum_valid_span;
    }
};
