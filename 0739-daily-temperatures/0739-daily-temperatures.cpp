/*
 * Approach: Monotonic stack of indices with decreasing temperatures. Each new
 * day pops every colder day still waiting and fills in its answer as the
 * index distance. Each index is pushed and popped at most once.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        vector<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && temperatures[st.back()] < temperatures[i]) {
                ans[st.back()] = i - st.back();
                st.pop_back();
            }
            st.push_back(i);
        }
        return ans;
    }
};
