/*
 * Approach: greedy with two pointers on the sorted weights. The heaviest
 * remaining person always takes a boat; if the lightest remaining person
 * fits alongside them, they share it.
 *
 * Time:  O(n log n)
 * Space: O(1) extra (sorting in place)
 */
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int lo = 0, hi = (int)people.size() - 1, boats = 0;
        while (lo <= hi) {
            if (people[lo] + people[hi] <= limit) ++lo;
            --hi;
            ++boats;
        }
        return boats;
    }
};
