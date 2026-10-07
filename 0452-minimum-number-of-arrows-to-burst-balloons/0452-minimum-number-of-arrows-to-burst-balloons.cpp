class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;
        
        // Sort balloons based on their end coordinates
        // Using a lambda function prevents integer overflow issues that a - b might cause
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        int arrows = 1;
        int current_end = points[0][1];
        
        for (int i = 1; i < points.size(); ++i) {
            // If the current balloon starts after the previous arrow's position,
            // we need a new arrow.
            if (points[i][0] > current_end) {
                arrows++;
                current_end = points[i][1]; // Move arrow position to current balloon's end
            }
        }
        
        return arrows;
    }
};
