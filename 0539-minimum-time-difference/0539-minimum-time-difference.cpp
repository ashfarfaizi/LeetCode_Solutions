#include <vector>
#include <string>
#include <algorithm>
#include <climits>

class Solution {
public:
    int findMinDifference(std::vector<std::string>& timePoints) {
        // Pigeonhole Principle: If there are more times than minutes in a day, 
        // there must be at least one duplicate.
        if (timePoints.size() > 1440) return 0;
        
        std::vector<int> minutes;
        minutes.reserve(timePoints.size());
        
        // Convert all time strings into absolute minutes from 00:00
        for (const std::string& time : timePoints) {
            int h = (time[0] - '0') * 10 + (time[1] - '0');
            int m = (time[3] - '0') * 10 + (time[4] - '0');
            minutes.push_back(h * 60 + m);
        }
        
        // Sort the time points in ascending order
        std::sort(minutes.begin(), minutes.end());
        
        int min_diff = INT_MAX;
        
        // Find the minimum difference between adjacent times
        for (size_t i = 1; i < minutes.size(); ++i) {
            min_diff = std::min(min_diff, minutes[i] - minutes[i - 1]);
        }
        
        // Account for the wrap-around difference between the last and first time across midnight
        int wrap_around_diff = (1440 - minutes.back()) + minutes[0];
        min_diff = std::min(min_diff, wrap_around_diff);
        
        return min_diff;
    }
};
