#include <vector>
#include <stack>

class Solution {
public:
    std::vector<int> nextGreaterElements(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> result(n, -1);
        std::stack<int> st; // Stores elements (or indices)
        
        // Traverse the array twice to simulate circular behavior
        for (int i = 2 * n - 1; i >= 0; --i) {
            int current_val = nums[i % n];
            
            // Pop elements from the stack that are smaller or equal
            while (!st.empty() && st.top() <= current_val) {
                st.pop();
            }
            
            // During the actual array bounds pass, record the answer
            if (i < n) {
                if (!st.empty()) {
                    result[i] = {st.top()};
                }
            }
            
            // Push the current value onto the stack
            st.push(current_val);
        }
        
        return result;
    }
};
