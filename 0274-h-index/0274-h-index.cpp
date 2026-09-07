#include <vector>
#include <algorithm>

class Solution {
public:
    int hIndex(std::vector<int>& citations) {
        // Sort citations in descending order
        std::sort(citations.begin(), citations.end(), std::greater<int>());
        
        int h = 0;
        // Count how many papers have citations >= their 1-based index position
        while (h < citations.size() && citations[h] > h) {
            h++;
        }
        
        return h;
    }
};
