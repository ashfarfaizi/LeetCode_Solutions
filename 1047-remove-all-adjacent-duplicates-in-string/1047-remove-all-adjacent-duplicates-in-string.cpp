/*
 * Approach: Treat the output string as a stack. If the incoming character
 * matches the top, the pair cancels (pop); otherwise push it. Cascading
 * removals happen naturally because the new top is checked next time.
 *
 * Time:  O(n)
 * Space: O(n) for the result
 */
class Solution {
public:
    string removeDuplicates(string s) {
        string st;
        st.reserve(s.size());
        for (char c : s) {
            if (!st.empty() && st.back() == c) st.pop_back();
            else st.push_back(c);
        }
        return st;
    }
};
