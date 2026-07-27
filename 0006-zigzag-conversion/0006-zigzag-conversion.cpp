class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size();

        if (numRows == 1 || numRows >= n)
            return s;

        string result;
        result.reserve(n);

        int cycle = 2 * (numRows - 1);

        for (int row = 0; row < numRows; ++row) {
            for (int start = row; start < n; start += cycle) {
                result += s[start];

                int diagonal = start + cycle - 2 * row;

                if (row != 0 &&
                    row != numRows - 1 &&
                    diagonal < n) {
                    result += s[diagonal];
                }
            }
        }

        return result;
    }
};