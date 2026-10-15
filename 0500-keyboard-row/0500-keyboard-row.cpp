#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        // String representing the row index (0, 1, or 2) for each alphabet from a-z
        // Corresponding index:  a b c d e f g h i j k l m n o p q r s t u v w x y z
        string row_map =        "12210111011122000010020202";
        
        vector<string> result;
        
        for (const string& word : words) {
            bool valid = true;
            // Identify row of the first character (handling lowercase/uppercase)
            int target_row = row_map[tolower(word[0]) - 'a'];
            
            for (char c : word) {
                if (row_map[tolower(c) - 'a'] != target_row) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                result.push_back(word);
            }
        }
        
        return result;
    }
};
