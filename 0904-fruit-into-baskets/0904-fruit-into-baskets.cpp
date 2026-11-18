/*
 * Approach: this is the longest subarray with at most two distinct values.
 * Slide a window, counting fruit types in a map, and shrink from the left
 * whenever a third type enters.
 *
 * Time:  O(n)
 * Space: O(1) (the map never holds more than three keys)
 */
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> count;
        int best = 0;
        for (int left = 0, right = 0; right < (int)fruits.size(); ++right) {
            ++count[fruits[right]];
            while (count.size() > 2) {
                if (--count[fruits[left]] == 0) count.erase(fruits[left]);
                ++left;
            }
            best = max(best, right - left + 1);
        }
        return best;
    }
};
