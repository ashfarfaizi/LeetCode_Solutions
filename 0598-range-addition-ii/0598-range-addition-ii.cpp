/*
 * Approach: Every operation increments the top-left a x b rectangle, so the
 * cells touched by all operations hold the maximum. That region is the
 * intersection of the rectangles: min of all a by min of all b.
 * Time: O(k) for k operations, Space: O(1)
 */
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int rows = m, cols = n;
        for (auto& op : ops) {
            rows = min(rows, op[0]);
            cols = min(cols, op[1]);
        }
        return rows * cols;
    }
};
