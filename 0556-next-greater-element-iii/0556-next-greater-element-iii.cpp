/*
 * Approach: Treat the digits like a permutation and compute the next
 * permutation: find the rightmost digit smaller than its right neighbour, swap it
 * with the smallest larger digit to its right, then reverse the suffix. Return -1
 * if no such permutation exists or the result overflows 32 bits.
 * Time: O(d) where d is the number of digits, Space: O(d)
 */
class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        int i = static_cast<int>(s.size()) - 2;
        while (i >= 0 && s[i] >= s[i + 1]) --i;
        if (i < 0) return -1;
        int j = static_cast<int>(s.size()) - 1;
        while (s[j] <= s[i]) --j;
        swap(s[i], s[j]);
        reverse(s.begin() + i + 1, s.end());
        long long v = stoll(s);
        return v > INT_MAX ? -1 : static_cast<int>(v);
    }
};
