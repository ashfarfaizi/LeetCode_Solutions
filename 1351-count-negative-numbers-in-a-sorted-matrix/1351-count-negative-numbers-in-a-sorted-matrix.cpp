/*
 * Approach: Staircase walk. Start at the bottom-left corner. If the value is
 * negative, everything to its right in that row is negative too, so add
 * them all and move up a row; otherwise move one column right.
 *
 * Time:  O(m + n)
 * Space: O(1)
 */
class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int r = m - 1, c = 0, count = 0;
        while (r >= 0 && c < n) {
            if (grid[r][c] < 0) {
                count += n - c;
                --r;
            } else {
                ++c;
            }
        }
        return count;
    }
};
