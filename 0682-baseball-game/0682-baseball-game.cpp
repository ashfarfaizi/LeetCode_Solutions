/*
 * Approach: Stack simulation. Integers are pushed, "+" pushes the sum of the
 * top two, "D" pushes double the top, and "C" pops the top. The answer is
 * the sum of whatever remains on the stack.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    int calPoints(vector<string>& operations) {
        vector<int> st;
        for (const string& op : operations) {
            if (op == "+") {
                st.push_back(st[st.size() - 1] + st[st.size() - 2]);
            } else if (op == "D") {
                st.push_back(2 * st.back());
            } else if (op == "C") {
                st.pop_back();
            } else {
                st.push_back(stoi(op));
            }
        }
        return accumulate(st.begin(), st.end(), 0);
    }
};
