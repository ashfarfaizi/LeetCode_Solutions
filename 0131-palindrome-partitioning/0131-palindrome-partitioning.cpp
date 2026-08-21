#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    // Helper function to check if a substring is a palindrome
    bool isPalindrome(const string& s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end]) {
                return false;
            }
            start++;
            end--;
        }
        return true;
    }

    // Backtracking function to explore all valid partitioning splits
    void backtrack(const string& s, int startIndex, vector<string>& currentPath, vector<vector<string>>& results) {
        // Base Case: If the start index reaches the end of the string, a valid partitioning is found
        if (startIndex == s.length()) {
            results.push_back(currentPath);
            return;
        }

        // Explore all possible substrings starting from startIndex
        for (int endIndex = startIndex; endIndex < s.length(); ++endIndex) {
            // Check if the current substring fraction s[startIndex...endIndex] is a palindrome
            if (isPalindrome(s, startIndex, endIndex)) {
                // Action: Choose the valid palindromic substring segment
                string substring = s.substr(startIndex, endIndex - startIndex + 1);
                currentPath.push_back(substring);

                // Recurse: Continue to partition the remaining suffix slice of the string
                backtrack(s, endIndex + 1, currentPath, results);

                // Backtrack: Revert choice for the next loop iteration step
                currentPath.pop_back();
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<string> currentPath;
        backtrack(s, 0, currentPath, results);
        return results;
    }
};
