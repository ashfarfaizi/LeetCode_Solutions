/*
 * Approach: simulate the stack. Push each value from pushed in order, and
 * after each push pop greedily while the top equals the next value expected
 * in popped. The sequences are consistent exactly when every value gets
 * popped by the end.
 *
 * Time:  O(n)
 * Space: O(n)
 */
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        vector<int> st;
        size_t j = 0;
        for (int x : pushed) {
            st.push_back(x);
            while (!st.empty() && j < popped.size() && st.back() == popped[j]) {
                st.pop_back();
                ++j;
            }
        }
        return j == popped.size();
    }
};
