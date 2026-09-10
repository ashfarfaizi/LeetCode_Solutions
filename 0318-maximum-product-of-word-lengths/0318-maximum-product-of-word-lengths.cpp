#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    int maxProduct(std::vector<std::string>& words) {
        int n = words.size();
        std::vector<int> masks(n, 0);
        
        // 1. Compute the bitmask for each word
        for (int i = 0; i < n; ++i) {
            for (char c : words[i]) {
                masks[i] |= (1 << (c - 'a'));
            }
        }
        
        int max_prod = 0;
        
        // 2. Compare pairs to find the maximum length product
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // If bitwise AND is 0, the two words share no common letters
                if ((masks[i] & masks[j]) == 0) {
                    int current_prod = words[i].length() * words[j].length();
                    max_prod = std::max(max_prod, current_prod);
                }
            }
        }
        
        return max_prod;
    }
};
