/*
 * Approach: The skyline from the north/south is the max of each column and
 * from the east/west the max of each row. A cell can rise to the smaller of
 * its row max and column max without changing either view, so sum that gap.
 * Time: O(n^2), Space: O(n)
 */
class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> rowMax(n, 0), colMax(n, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                rowMax[i] = max(rowMax[i], grid[i][j]);
                colMax[j] = max(colMax[j], grid[i][j]);
            }
        int total = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                total += min(rowMax[i], colMax[j]) - grid[i][j];
        return total;
    }
};
