#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCut(string s) {
        int n = s.length();
        if (n <= 1) return 0;

        // cuts[i] stores the minimum cuts needed for prefix s[0...i]
        vector<int> cuts(n);
        for (int i = 0; i < n; ++i) {
            cuts[i] = i; // Maximum possible cuts (cut after every character)
        }

        // Center expansion approach to find palindromes and update cuts in-place
        for (int mid = 0; mid < n; ++mid) {
            // Case 1: Odd-length palindromes centered at 'mid' (e.g., "aba")
            int start = mid, end = mid;
            while (start >= 0 && end < n && s[start] == s[end]) {
                if (start == 0) {
                    cuts[end] = 0; // Entire prefix s[0...end] is a palindrome
                } else {
                    cuts[end] = min(cuts[end], cuts[start - 1] + 1);
                }
                start--;
                end++;
            }

            // Case 2: Even-length palindromes centered between 'mid' and 'mid+1' (e.g., "baab")
            start = mid;
            end = mid + 1;
            while (start >= 0 && end < n && s[start] == s[end]) {
                if (start == 0) {
                    cuts[end] = 0; // Entire prefix s[0...end] is a palindrome
                } else {
                    cuts[end] = min(cuts[end], cuts[start - 1] + 1);
                }
                start--;
                end++;
            }
        }

        return cuts[n - 1];
    }
};
