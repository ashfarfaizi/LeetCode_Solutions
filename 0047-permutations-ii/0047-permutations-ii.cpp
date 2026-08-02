class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if (nums.empty()) return {};
        
        int total_target_length = nums.size();
        
        // Step 1: Compress duplicates into a unique key-capacity profile map
        unordered_map<int, int> global_element_capacities;
        for (int value : nums) {
            global_element_capacities[value]++;
        }
        
        // Step 2: Initialize layer progression with an empty baseline container
        vector<vector<int>> active_layer_permutations = {{}};
        
        // Step 3: Expand the combinations layer-by-layer up to the target length
        for (int step = 0; step < total_target_length; ++step) {
            vector<vector<int>> next_layer_permutations;
            
            for (const auto& incomplete_sequence : active_layer_permutations) {
                // Calculate current inline item frequencies for the specific active branch
                unordered_map<int, int> current_sequence_counts;
                for (int value : incomplete_sequence) {
                    current_sequence_counts[value]++;
                }
                
                // Scan unique available tokens to generate unique extensions
                for (const auto& bucket : global_element_capacities) {
                    int unique_value = bucket.first;
                    int permitted_max_capacity = bucket.second;
                    
                    // Verify if this unique value can still be assigned to the sequence
                    if (current_sequence_counts[unique_value] < permitted_max_capacity) {
                        vector<int> extended_sequence = incomplete_sequence;
                        extended_sequence.push_back(unique_value);
                        
                        // FIXED: Aligned the variable naming cleanly to extended_sequence
                        next_layer_permutations.push_back(std::move(extended_sequence));
                    }
                }
            }
            
            // Advance the state matrix to become the new processing layer
            active_layer_permutations = std::move(next_layer_permutations);
        }
        
        return active_layer_permutations;
    }
};
