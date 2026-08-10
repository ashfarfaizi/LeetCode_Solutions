#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int max_area = 0;
        int n = heights.size();

        // Loop up to n to seamlessly flush remaining bars using a virtual 0-height bar
        for (int i = 0; i <= n; ++i) {
            // Assign a sentinel height of 0 at the virtual index n
            int current_height = (i == n) ? 0 : heights[i];

            // Maintain monotonic increasing property of the stack
            while (!st.empty() && current_height < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();

                // Determine the width of the rectangle
                // If the stack is empty, the bar can extend all the way back to index 0
                int width = st.empty() ? i : i - st.top() - 1;

                max_area = max(max_area, height * width);
            }
            
            // Push current index onto the stack
            st.push(i);
        }

        return max_area;
    }
};
