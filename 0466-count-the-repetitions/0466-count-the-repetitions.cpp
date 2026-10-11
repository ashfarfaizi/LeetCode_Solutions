#include <string>
#include <vector>
#include <unordered_map>

class Solution {
public:
    int getMaxRepetitions(std::string s1, int n1, std::string s2, int n2) {
        int len1 = s1.length();
        int len2 = s2.length();
        
        // s1_count keeps track of how many blocks of s1 we have processed
        // s2_count keeps track of how many fully completed s2 strings we found
        int s1_count = 0, s2_count = 0;
        int index = 0; // Current pointer in s2
        
        // Maps the index of s2 to a pair: {s1_count, s2_count}
        // Since index can only take values from 0 to len2-1, there are at most len2 states.
        std::unordered_map<int, std::pair<int, int>> seen;
        
        while (s1_count < n1) {
            s1_count++;
            
            // Scan through one full s1 block character by character
            for (int i = 0; i < len1; ++i) {
                if (s1[i] == s2[index]) {
                    index++;
                    if (index == len2) {
                        s2_count++;
                        index = 0;
                    }
                }
            }
            
            // Check if we have encountered this exact s2 state (index) before
            if (seen.count(index)) {
                auto [prev_s1_count, prev_s2_count] = seen[index];
                
                // Calculate lengths of the repeating cycle
                int cycle_s1_length = s1_count - prev_s1_count;
                int cycle_s2_length = s2_count - prev_s2_count;
                
                // Determine how many full cycles can fit in the remaining s1 blocks
                int remaining_s1_blocks = n1 - s1_count;
                int full_cycles = remaining_s1_blocks / cycle_s1_length;
                
                // Add the s2 counts gained from the skipping all full cycles
                s2_count += full_cycles * cycle_s2_length;
                s1_count += full_cycles * cycle_s1_length;
            } else {
                // Record the counts at this specific state
                seen[index] = {s1_count, s2_count};
            }
        }
        
        // Total s2 strings found divided by n2 gives the maximum 'm' repetitions
        return s2_count / n2;
    }
};
