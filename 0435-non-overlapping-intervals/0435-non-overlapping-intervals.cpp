#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        // Sort the intervals based on their end times
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        int removals = 0;
        // Track the end time of the last added non-overlapping interval
        int prevEnd = intervals[0][1];
        
        for (size_t i = 1; i < intervals.size(); ++i) {
            // If the current interval starts before the previous one ends, it's an overlap
            if (intervals[i][0] < prevEnd) {
                removals++;
            } else {
                // No overlap, update the end boundary to the current interval's end
                prevEnd = intervals[i][1];
            }
        }
        
        return removals;
    }
};
