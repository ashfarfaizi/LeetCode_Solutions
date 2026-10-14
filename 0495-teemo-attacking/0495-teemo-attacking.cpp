class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.empty() || duration == 0) return 0;
        
        int totalDuration = 0;
        
        // Loop through all attacks except the last one
        for (size_t i = 0; i < timeSeries.size() - 1; ++i) {
            int gap = timeSeries[i + 1] - timeSeries[i];
            // Take the smaller value: either the gap until the next attack or the full duration
            totalDuration += min(gap, duration);
        }
        
        // The last attack always inflicts the full poison duration
        totalDuration += duration;
        
        return totalDuration;
    }
};
