#include <vector>
#include <algorithm>

class Solution {
public:
    int findContentChildren(std::vector<int>& g, std::vector<int>& s) {
        // Step 1: Sort both arrays
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());
        
        int child_ptr = 0;
        int cookie_ptr = 0;
        
        // Step 2: Use two pointers to match cookies to children
        while (child_ptr < g.size() && cookie_ptr < s.size()) {
            if (s[cookie_ptr] >= g[child_ptr]) {
                // Child is satisfied, move to the next child
                child_ptr++;
            }
            // Move to the next cookie regardless
            cookie_ptr++;
        }
        
        return child_ptr;
    }
};
