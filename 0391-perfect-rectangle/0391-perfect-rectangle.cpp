#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        // Track the boundaries of the large overarching rectangle
        int min_x = INT_MAX, min_y = INT_MAX;
        int max_x = INT_MIN, max_y = INT_MIN;
        
        long long total_area = 0;
        unordered_set<string> point_set;
        
        for (const auto& rect : rectangles) {
            int x1 = rect[0], y1 = rect[1];
            int x2 = rect[2], y2 = rect[3];
            
            // Update the extreme corners for the bounding box
            min_x = min(min_x, x1);
            min_y = min(min_y, y1);
            max_x = max(max_x, x2);
            max_y = max(max_y, y2);
            
            // Sum up individual rectangle areas (cast to long long to prevent overflow)
            total_area += (long long)(x2 - x1) * (y2 - y1);
            
            // Create unique string representations for the 4 corners of the current rectangle
            string p1 = to_string(x1) + "," + to_string(y1);
            string p2 = to_string(x1) + "," + to_string(y2);
            string p3 = to_string(x2) + "," + to_string(y1);
            string p4 = to_string(x2) + "," + to_string(y2);
            
            // Apply the symmetric difference rule (XOR behavior): 
            // If the point exists, remove it (it's shared/internal). If not, add it.
            for (const string& p : {p1, p2, p3, p4}) {
                if (point_set.count(p)) {
                    point_set.erase(p);
                } else {
                    point_set.insert(p);
                }
            }
        }
        
        // Condition 1: Check if the four extreme corners of the bounding box exist in the set
        string check1 = to_string(min_x) + "," + to_string(min_y);
        string check2 = to_string(min_x) + "," + to_string(max_y);
        string check3 = to_string(max_x) + "," + to_string(min_y);
        string check4 = to_string(max_x) + "," + to_string(max_y);
        
        if (point_set.size() != 4 || 
            !point_set.count(check1) || !point_set.count(check2) || 
            !point_set.count(check3) || !point_set.count(check4)) {
            return false;
        }
        
        // Condition 2: Check if the sum of small areas equals the large bounding area
        long long bounding_area = (long long)(max_x - min_x) * (max_y - min_y);
        
        return total_area == bounding_area;
    }
};
