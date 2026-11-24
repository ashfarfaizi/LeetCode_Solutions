/*
 * Approach: Greedy with a monotonic decreasing stack. Building the tree is
 * equivalent to repeatedly removing a leaf a at cost a * (smaller of its
 * current neighbours that are larger). Each value, when popped because a
 * larger value arrives, pairs with the smaller of that new value and the
 * element below it on the stack. Leftover stack values pair consecutively.
 *
 * Time:  O(n)
 * Space: O(n)
 */
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int cost = 0;
        vector<int> st = {INT_MAX};
        for (int x : arr) {
            while (st.back() <= x) {
                int mid = st.back();
                st.pop_back();
                cost += mid * min(st.back(), x);
            }
            st.push_back(x);
        }
        for (size_t i = 2; i < st.size(); ++i) cost += st[i] * st[i - 1];
        return cost;
    }
};
