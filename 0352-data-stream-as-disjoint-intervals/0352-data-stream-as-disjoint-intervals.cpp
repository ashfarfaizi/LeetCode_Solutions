#include <vector>
#include <set>

class SummaryRanges {
private:
    // Set to store disjoint intervals sorted by their starting values
    std::set<std::pair<int, int>> intervals;

public:
    SummaryRanges() {
        // Constructor initializes an empty data stream
    }
    
    void addNum(int value) {
        // Find the first interval that starts strictly after 'value'
        auto it = intervals.upper_bound({value, 1e9});
        
        int start = value, end = value;
        bool hasLeft = (it != intervals.begin());
        auto leftIt = hasLeft ? std::prev(it) : it;
        
        // Scenario 4 (subset check): If 'value' falls inside the left interval, do nothing
        if (hasLeft && leftIt->second >= value) {
            return;
        }
        
        // Scenario 1 & 2: Check if 'value' can merge with the left interval
        if (hasLeft && leftIt->second + 1 == value) {
            start = leftIt->first;
            intervals.erase(leftIt);
        }
        
        // Scenario 1 & 3: Check if 'value' can merge with the right interval
        if (it != intervals.end() && it->first == value + 1) {
            end = it->second;
            intervals.erase(it);
        }
        
        // Insert the newly formed or merged interval
        intervals.insert({start, end});
    }
    
    std::vector<std::vector<int>> getIntervals() {
        std::vector<std::vector<int>> res;
        for (const auto& p : intervals) {
            res.push_back({p.first, p.second});
        }
        return res;
    }
};
