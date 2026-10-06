#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> result(n, -1);
        
        // Map to store: start_point -> original_index
        // std::map is automatically sorted by key (start_point)
        map<int, int> startMap;
        for (int i = 0; i < n; ++i) {
            startMap[intervals[i][0]] = i;
        }
        
        // Find the right interval for each element
        for (int i = 0; i < n; ++i) {
            int targetEnd = intervals[i][1];
            
            // lower_bound finds the first key >= targetEnd
            auto it = startMap.lower_bound(targetEnd);
            
            if (it != startMap.end()) {
                result[i] = it->second; // Store the original index
            }
        }
        
        return result;
    }
};
