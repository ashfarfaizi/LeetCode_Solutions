/*
 * Approach: count every row (as a vector key) in a map, then build each
 * column and add how many identical rows were seen.
 * Time: O(n^2 log n), Space: O(n^2)
 */
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        map<vector<int>, int> rows;
        for (auto& row : grid) ++rows[row];
        int pairs = 0;
        for (int c = 0; c < n; ++c) {
            vector<int> col(n);
            for (int r = 0; r < n; ++r) col[r] = grid[r][c];
            auto it = rows.find(col);
            if (it != rows.end()) pairs += it->second;
        }
        return pairs;
    }
};
