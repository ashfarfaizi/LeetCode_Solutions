#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        // Convert bank to a hash set for quick O(1) lookups
        unordered_set<string> bankSet(bank.begin(), bank.end());
        
        // If the destination gene is not in the valid bank, it's unreachable
        if (bankSet.find(endGene) == bankSet.end()) {
            return -1;
        }
        
        // Queue stores pairs of {current_gene_string, current_mutation_level}
        queue<pair<string, int>> q;
        q.push({startGene, 0});
        
        // The possible choice of characters at any gene position
        vector<char> choices = {'A', 'C', 'G', 'T'};
        
        while (!q.empty()) {
            auto [currentGene, steps] = q.front();
            q.pop();
            
            // Base case: destination reached
            if (currentGene == endGene) {
                return steps;
            }
            
            // Try mutating every character position
            for (int i = 0; i < 8; ++i) {
                char originalChar = currentGene[i];
                
                for (char c : choices) {
                    if (c == originalChar) continue; // Skip identical character
                    
                    currentGene[i] = c; // Mutate character
                    
                    // If the mutated gene is valid and hasn't been visited yet
                    if (bankSet.find(currentGene) != bankSet.end()) {
                        q.push({currentGene, steps + 1});
                        bankSet.erase(currentGene); // Mark as visited by erasing from set
                    }
                }
                
                currentGene[i] = originalChar; // Revert back for the next iteration
            }
        }
        
        return -1; // If endGene is never reached
    }
};
