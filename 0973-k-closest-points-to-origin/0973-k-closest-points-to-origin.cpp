/*
 * Approach: quickselect via nth_element on squared distance. After
 * partitioning around the k-th smallest distance, the first k points are
 * exactly the k closest (in any order). Squared distances avoid sqrt and
 * fit comfortably in an int for coordinates up to 10^4.
 *
 * Time:  O(n) average
 * Space: O(1) extra (in place)
 */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        auto dist = [](const vector<int>& p) { return p[0] * p[0] + p[1] * p[1]; };
        nth_element(points.begin(), points.begin() + k - 1, points.end(),
                    [&](const vector<int>& a, const vector<int>& b) { return dist(a) < dist(b); });
        return vector<vector<int>>(points.begin(), points.begin() + k);
    }
};
