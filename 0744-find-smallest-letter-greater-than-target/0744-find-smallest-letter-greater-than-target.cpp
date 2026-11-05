/*
 * Approach: Binary search (upper_bound) for the first letter strictly greater
 * than target; if it runs off the end, wrap around to the first letter.
 * Time: O(log n), Space: O(1)
 */
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        auto it = upper_bound(letters.begin(), letters.end(), target);
        return it == letters.end() ? letters[0] : *it;
    }
};
