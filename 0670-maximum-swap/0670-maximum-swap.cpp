/*
 * Approach: Greedy on digits. Record the last index of each digit 0-9. Scan
 * left to right; for the first position where a larger digit appears later,
 * swap it with the last occurrence of the largest such digit.
 * Time: O(d) where d is the number of digits, Space: O(d)
 */
class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        int last[10];
        fill(last, last + 10, -1);
        for (int i = 0; i < (int)s.size(); ++i) last[s[i] - '0'] = i;
        for (int i = 0; i < (int)s.size(); ++i) {
            for (int d = 9; d > s[i] - '0'; --d) {
                if (last[d] > i) {
                    swap(s[i], s[last[d]]);
                    return stoi(s);
                }
            }
        }
        return num;
    }
};
