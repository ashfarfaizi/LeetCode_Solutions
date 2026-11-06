/*
 * Approach: Hashing. For each row record the prefix-sum positions of its
 * internal brick edges (excluding the wall's right border). The vertical line
 * through the most common edge position crosses the fewest bricks:
 * rows - maxEdgeCount.
 * Time: O(total bricks), Space: O(distinct edge positions)
 */
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> edges;
        int best = 0;
        for (auto& row : wall) {
            int pos = 0;
            for (size_t i = 0; i + 1 < row.size(); ++i) {
                pos += row[i];
                best = max(best, ++edges[pos]);
            }
        }
        return static_cast<int>(wall.size()) - best;
    }
};
