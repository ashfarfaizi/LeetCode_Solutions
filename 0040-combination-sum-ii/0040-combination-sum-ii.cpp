class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        // Step 1: Compress duplicates into a frequency lookup matrix
        // This replaces the standard array-sorting paradigm
        unordered_map<int, int> element_frequencies;
        for (int num : candidates) {
            if (num <= target) {
                element_frequencies[num]++;
            }
        }
        
        // Convert map to a flat vector of unique pairs to maintain deterministic traversal
        vector<pair<int, int>> unique_items;
        for (auto& entry : element_frequencies) {
            unique_items.push_back(entry);
        }
        
        // Step 2: Use an explicit multi-layer state vector to track possible subset paths
        // state_paths[current_sum] contains all unique item-combinations that reach that sum
        vector<vector<vector<int>>> state_paths(target + 1);
        state_paths[0] = {{}}; // Base state: an empty combination achieves a sum of 0
        
        // Step 3: Expand the states using knapsack-style combinations
        for (const auto& item : unique_items) {
            int value = item.first;
            int max_count = item.second;
            
            // Traverse backward to prevent an item from tracking its own newly created configurations in the same phase
            for (int current_sum = target; current_sum >= 0; --current_sum) {
                if (state_paths[current_sum].empty()) continue;
                
                // Try incorporating multiple copies of the current unique element up to its available limit
                for (int count = 1; count <= max_count; ++count) {
                    int added_value = count * value;
                    int next_sum = current_sum + added_value;
                    
                    if (next_sum > target) break;
                    
                    // Replicate combinations from state_paths[current_sum], adding 'count' instances of 'value'
                    for (const auto& existing_path : state_paths[current_sum]) {
                        vector<int> extended_path = existing_path;
                        extended_path.insert(extended_path.end(), count, value);
                        state_paths[next_sum].push_back(extended_path);
                    }
                }
            }
        }
        
        return state_paths[target];
    }
};
