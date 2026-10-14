class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> next_greater;
        stack<int> st;
        
        // Traverse nums2 to find the next greater element for every number
        for (int num : nums2) {
            // While stack is not empty and current number is greater than the stack's top element
            while (!st.empty() && st.top() < num) {
                next_greater[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }
        
        // Build the result vector for nums1 using our precomputed map
        vector<int> ans;
        ans.reserve(nums1.size());
        for (int num : nums1) {
            if (next_greater.count(num)) {
                ans.push_back(next_greater[num]);
            } else {
                ans.push_back(-1); // No next greater element found
            }
        }
        
        return ans;
    }
};
