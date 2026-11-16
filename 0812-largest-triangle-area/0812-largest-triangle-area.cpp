/*
 * Approach: With at most 50 points, try every triple and compute its area
 * with the shoelace formula: |x1(y2-y3) + x2(y3-y1) + x3(y1-y2)| / 2.
 * Time: O(n^3), Space: O(1)
 */
class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int n = points.size();
        double best = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                for (int k = j + 1; k < n; ++k) {
                    const auto &a = points[i], &b = points[j], &c = points[k];
                    double area = 0.5 * abs(a[0] * (b[1] - c[1]) +
                                            b[0] * (c[1] - a[1]) +
                                            c[0] * (a[1] - b[1]));
                    best = max(best, area);
                }
        return best;
    }
};
