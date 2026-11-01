/*
 * Approach: Store pairs (value, minimum so far) on a single stack so the
 * current minimum is always available at the top.
 * Time: O(1) per operation, Space: O(n)
 */
class MinStack {
    vector<pair<int, int>> st;
public:
    MinStack() {}

    void push(int val) {
        int m = st.empty() ? val : min(val, st.back().second);
        st.emplace_back(val, m);
    }

    void pop() { st.pop_back(); }

    int top() { return st.back().first; }

    int getMin() { return st.back().second; }
};
