/*
 * Approach: The k-th element in row-major order sits at (k / n, k % n) in the
 * source and at (k / c, k % c) in the result, so copy with a single index.
 * Time: O(m*n), Space: O(m*n) for the output
 */
class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m = mat.size(), n = mat[0].size();
        if (m * n != r * c) return mat;
        vector<vector<int>> res(r, vector<int>(c));
        for (int k = 0; k < m * n; ++k) res[k / c][k % c] = mat[k / n][k % n];
        return res;
    }
};
