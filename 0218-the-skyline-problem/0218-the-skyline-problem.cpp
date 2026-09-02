#include <vector>
#include <algorithm>
#include <set>

class Solution {
public:
    std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings) {
        // Collect critical sweep-line events
        // Each event is a pair: {x_coordinate, height_modifier}
        std::vector<std::pair<int, int>> events;
        for (const auto& b : buildings) {
            events.push_back({b[0], -b[2]}); // Start wall: negative height
            events.push_back({b[1], b[2]});  // End wall: positive height
        }
        
        // Sort events according to our custom rule requirements
        std::sort(events.begin(), events.end());
        
        std::vector<std::vector<int>> result;
        
        // Multiset acts as a Max-Heap that allows clean arbitrary value deletion
        std::multiset<int> active_heights = {0}; // Ground baseline height is 0
        int max_current_height = 0;
        
        for (const auto& event : events) {
            int x = event.first;
            int h = event.second;
            
            if (h < 0) {
                // It's a start wall, insert its original positive height
                active_heights.insert(-h);
            } else {
                // It's an end wall, erase exactly one instance of this height
                active_heights.erase(active_heights.find(h));
            }
            
            // The largest element is always positioned at the very end of the multiset
            int highest_active = *active_heights.rbegin();
            
            // If the absolute peak shifts, we have a milestone coordinate shift
            if (highest_active != max_current_height) {
                result.push_back({x, highest_active});
                max_current_height = highest_active;
            }
        }
        
        return result;
    }
};
