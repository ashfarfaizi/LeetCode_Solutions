/*
 * Approach: use the result string as a stack. Push each character, but pop
 * instead when it is the opposite-case twin of the current top.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    string makeGood(string s) {
        string st;
        for (char ch : s) {
            if (!st.empty() && st.back() != ch && tolower(st.back()) == tolower(ch))
                st.pop_back();
            else
                st.push_back(ch);
        }
        return st;
    }
};
