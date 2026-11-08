/*
 * Approach: Direct simulation. For every cell sum the up to nine in-bounds
 * cells of its 3x3 neighbourhood, count them, and store the integer average
 * in a separate output matrix.
 * Time: O(m * n), Space: O(m * n) for the output
 */
class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int m = img.size(), n = img[0].size();
        vector<vector<int>> out(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int sum = 0, cnt = 0;
                for (int r = max(0, i - 1); r <= min(m - 1, i + 1); ++r) {
                    for (int c = max(0, j - 1); c <= min(n - 1, j + 1); ++c) {
                        sum += img[r][c];
                        ++cnt;
                    }
                }
                out[i][j] = sum / cnt;
            }
        }
        return out;
    }
};
