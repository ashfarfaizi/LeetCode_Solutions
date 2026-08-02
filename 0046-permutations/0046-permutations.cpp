class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.empty()) return {};
        
        // Base State: Start with a single sequence containing only the first element
        vector<vector<int>> active_permutations = {{nums[0]}};
        
        // Process each remaining element sequentially to expand the permutation layer
        for (size_t element_idx = 1; element_idx < nums.size(); ++element_idx) {
            int target_inserted_value = nums[element_idx];
            vector<vector<int>> next_layer_permutations;
            
            // Replicate and insert the current number into all available structural slots
            for (const auto& individual_sequence : active_permutations) {
                size_t sequence_length = individual_sequence.size();
                
                // There are exactly sequence_length + 1 possible insertion slots
                for (size_t slot_position = 0; slot_position <= sequence_length; ++slot_position) {
                    vector<int> expanded_sequence = individual_sequence;
                    
                    // Insert the target number at the precise current slot boundary
                    expanded_sequence.insert(expanded_sequence.begin() + slot_position, target_inserted_value);
                    
                    next_layer_permutations.push_back(move(expanded_sequence));
                }
            }
            
            // Move the fully expanded layer forward to act as the next baseline state
            active_permutations = move(next_layer_permutations);
        }
        
        return active_permutations;
    }
};

