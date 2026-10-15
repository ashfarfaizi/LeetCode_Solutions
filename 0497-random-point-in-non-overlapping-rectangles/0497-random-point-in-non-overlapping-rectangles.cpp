#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int>> rectangles;
    vector<int> p_sums;
    int total_points;

public:
    Solution(vector<vector<int>>& rects) {
        rectangles = rects;
        total_points = 0;

        for (const auto& rect : rects) {
            // Number of integer points in the current rectangle
            long long points =
                (long long)(rect[2] - rect[0] + 1) * (rect[3] - rect[1] + 1);
            total_points += points;
            p_sums.push_back(total_points);
        }
    }

    vector<int> pick() {
        // Pick a random point index from 1 to total_points
        int target = rand() % total_points + 1;

        // Find the first rectangle that can cover this point index
        auto it = lower_bound(p_sums.begin(), p_sums.end(), target);
        int idx = distance(p_sums.begin(), it);

        const auto& rect = rectangles[idx];
        int a = rect[0], b = rect[1], x = rect[2], y = rect[3];

        // Calculate the relative point index inside this specific rectangle
        int prev_sum = (idx == 0) ? 0 : p_sums[idx - 1];
        int local_idx = target - prev_sum - 1; // 0-indexed local point

        int width = x - a + 1;

        // Convert the 1D local index into 2D X and Y offsets
        int x_coord = a + (local_idx % width);
        int y_coord = b + (local_idx / width);

        return {x_coord, y_coord};
    }
};
