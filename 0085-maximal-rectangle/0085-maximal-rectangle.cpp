#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function to calculate the largest rectangle area in a 1D histogram
    int largestRectangleArea(const vector<int>& heights) {
        stack<int> st;
        int max_area = 0;
        int n = heights.size();

        for (int i = 0; i <= n; ++i) {
            int current_height = (i == n) ? 0 : heights[i];

            while (!st.empty() && current_height < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();

                int width = st.empty() ? i : i - st.top() - 1;
                max_area = max(max_area, height * width);
            }
            st.push(i);
        }
        return max_area;
    }

public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<int> heights(cols, 0);
        int max_rectangle = 0;

        // Process the matrix row by row
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Update the histogram height for the current column
                if (matrix[i][j] == '1') {
                    heights[j]++;
                } else {
                    heights[j] = 0;
                }
            }
            // Calculate the maximal rectangle area for the current row's histogram
            max_rectangle = max(max_rectangle, largestRectangleArea(heights));
        }

        return max_rectangle;
    }
};
