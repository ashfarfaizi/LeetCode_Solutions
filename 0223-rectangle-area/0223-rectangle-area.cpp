#include <algorithm>

class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        // Calculate the individual areas of both rectangles using 64-bit int to avoid overflows
        long long areaA = (long long)(ax2 - ax1) * (ay2 - ay1);
        long long areaB = (long long)(bx2 - bx1) * (by2 - by1);
        
        // Find the overlapping dimensions
        int overlapWidth = std::min(ax2, bx2) - std::max(ax1, bx1);
        int overlapHeight = std::min(ay2, by2) - std::max(ay1, by1);
        
        // Compute overlap area only if they actually intersect on both axes
        long long overlapArea = 0;
        if (overlapWidth > 0 && overlapHeight > 0) {
            overlapArea = (long long)overlapWidth * overlapHeight;
        }
        
        // Return sum of both areas minus the common overlap
        return areaA + areaB - overlapArea;
    }
};
