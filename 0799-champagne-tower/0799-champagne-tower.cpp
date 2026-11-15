/*
 * Approach: Simulate row by row. Track how much liquid flows into each glass;
 * anything above 1 cup overflows and half goes to each glass beneath it.
 * The answer is min(1, flow into the queried glass).
 * Time: O(R^2), Space: O(R)
 */
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<double> row = {(double)poured};
        for (int r = 0; r < query_row; ++r) {
            vector<double> next(r + 2, 0.0);
            for (int i = 0; i <= r; ++i) {
                double extra = (row[i] - 1.0) / 2.0;
                if (extra > 0) {
                    next[i] += extra;
                    next[i + 1] += extra;
                }
            }
            row = move(next);
        }
        return min(1.0, row[query_glass]);
    }
};
