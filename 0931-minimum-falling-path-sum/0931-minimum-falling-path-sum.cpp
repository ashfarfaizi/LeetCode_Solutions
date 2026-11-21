/*
 * Approach: dynamic programming row by row. The cheapest path ending at
 * (r, c) is matrix[r][c] plus the cheapest of the three cells above it
 * (up-left, up, up-right). Keep only the previous row's costs and take the
 * minimum of the last row.
 *
 * Time:  O(n^2)
 * Space: O(n)
 */
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<int> prev = matrix[0], cur(n);
        for (int r = 1; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                int best = prev[c];
                if (c > 0) best = min(best, prev[c - 1]);
                if (c + 1 < n) best = min(best, prev[c + 1]);
                cur[c] = matrix[r][c] + best;
            }
            swap(prev, cur);
        }
        return *min_element(prev.begin(), prev.end());
    }
};
