class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        int bestStart = 0;
        int bestLength = 1;

        auto grow = [&](int left, int right) {
            while (left >= 0 && right < n && s[left] == s[right]) {
                --left;
                ++right;
            }

            int length = right - left - 1;

            if (length > bestLength) {
                bestLength = length;
                bestStart = left + 1;
            }
        };

        for (int center = 0; center < n; ++center) {
            // Odd-length palindrome
            grow(center, center);

            // Even-length palindrome
            grow(center, center + 1);
        }

        return s.substr(bestStart, bestLength);
    }
};