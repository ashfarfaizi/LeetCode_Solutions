#include <vector>
#include <stack>
#include <climits>

class Solution {
public:
    bool find132pattern(std::vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return false;
        
        std::stack<int> st;
        int third = INT_MIN; // Represents the '2' in the 132 pattern
        
        // Traverse the array backwards
        for (int i = n - 1; i >= 0; i--) {
            // If we find an element smaller than 'third', a 132 pattern is found
            if (nums[i] < third) {
                return true;
            }
            
            // If the current element is larger than the stack's top, 
            // it can act as the '3'. The popped values become candidates for '2'.
            while (!st.empty() && nums[i] > st.top()) {
                third = st.top();
                st.pop();
            }
            
            // Push current element as a potential '3'
            st.push(nums[i]);
        }
        
        return false;
    }
};
