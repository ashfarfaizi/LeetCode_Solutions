/*
 * Approach: Greedy with a monotonic stack. Scan left to right; while the last
 * kept digit is larger than the current one and deletions remain, drop it,
 * since lowering an earlier digit always wins. Any deletions left over come
 * off the end. Finally strip leading zeros.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    string removeKdigits(string num, int k) {
        string st;
        for (char c : num) {
            while (k > 0 && !st.empty() && st.back() > c) {
                st.pop_back();
                --k;
            }
            st.push_back(c);
        }
        st.resize(st.size() - min<size_t>(k, st.size()));
        size_t start = st.find_first_not_of('0');
        return start == string::npos ? "0" : st.substr(start);
    }
};
