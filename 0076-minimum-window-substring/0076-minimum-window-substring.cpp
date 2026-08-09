#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.length() < t.length()) {
            return "";
        }

        // ASCII frequency maps to store counts (supports upper/lowercase)
        vector<int> target_counts(128, 0);
        vector<int> window_counts(128, 0);

        // Populate required counts from string t
        int unique_chars_needed = 0;
        for (char c : t) {
            if (target_counts[c] == 0) {
                unique_chars_needed++;
            }
            target_counts[c]++;
        }

        int left = 0;
        int have = 0;
        int min_len = INT_MAX;
        int start_idx = -1;

        // Expand the sliding window via the right pointer
        for (int right = 0; right < s.length(); ++right) {
            char right_char = s[right];
            window_counts[right_char]++;

            // If the character is in t and matches the exact required frequency, increment 'have'
            if (target_counts[right_char] > 0 && window_counts[right_char] == target_counts[right_char]) {
                have++;
            }

            // Contract the window from the left as long as all characters are fully covered
            while (have == unique_chars_needed) {
                int current_window_len = right - left + 1;
                
                // Track and update the minimum window bounds seen so far
                if (current_window_len < min_len) {
                    min_len = current_window_len;
                    start_idx = left;
                }

                char left_char = s[left];
                window_counts[left_char]--;

                // If dropping this left character breaks the required target threshold, decrement 'have'
                if (target_counts[left_char] > 0 && window_counts[left_char] < target_counts[left_char]) {
                    have--;
                }
                
                left++; // Shrink the window left boundary
            }
        }

        // Return empty string if no valid window configuration was found
        return (start_idx == -1) ? "" : s.substr(start_idx, min_len);
    }
};
