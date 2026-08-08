#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i = 0;
        int n = words.size();

        while (i < n) {
            int j = i + 1;
            int line_words_length = words[i].length();
            
            // Greedily find how many words can fit into the current line
            while (j < n && line_words_length + words[j].length() + (j - i) <= maxWidth) {
                line_words_length += words[j].length();
                j++;
            }

            int num_words = j - i;
            int total_spaces = maxWidth - line_words_length;
            string current_line = "";

            // Condition: Last line or a line containing only a single word (Left-Justified)
            if (j == n || num_words == 1) {
                for (int k = i; k < j; ++k) {
                    current_line += words[k];
                    if (k < j - 1) {
                        current_line += " ";
                    }
                }
                // Append remaining padding spaces to fill out the maxWidth limit
                current_line += string(maxWidth - current_line.length(), ' ');
            } 
            // Condition: Standard line with multiple words (Fully-Justified)
            else {
                int gaps = num_words - 1;
                int base_spaces = total_spaces / gaps;
                int extra_spaces = total_spaces % gaps;

                for (int k = i; k < j; ++k) {
                    current_line += words[k];
                    if (k < j - 1) {
                        // Assign base spaces + 1 extra space if within left remainder count
                        int spaces_to_apply = base_spaces + (k - i < extra_spaces ? 1 : 0);
                        current_line += string(spaces_to_apply, ' ');
                    }
                }
            }

            result.push_back(current_line);
            i = j; // Advance to the next line group start index
        }

        return result;
    }
};
