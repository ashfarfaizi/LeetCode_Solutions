#include <vector>
#include <algorithm>

class Solution {
public:
    int hIndex(std::vector<int>& citations) {
        int n = citations.size();
        // Create buckets to store the count of papers for each citation number
        // Size is n + 1 to handle citations from 0 up to n+
        std::vector<int> buckets(n + 1, 0);
        
        for (int c : citations) {
            if (c >= n) {
                buckets[n]++; // Cap anything larger than n at n
            } else {
                buckets[c]++;
            }
        }
        
        int totalPapers = 0;
        // Iterate backward from the maximum possible h-index (n) down to 0
        for (int h = n; h >= 0; h--) {
            totalPapers += buckets[h];
            // If total papers found so far is >= current h, we found our H-Index
            if (totalPapers >= h) {
                return h;
            }
        }
        
        return 0;
    }
};
