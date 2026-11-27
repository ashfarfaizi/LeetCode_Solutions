/*
 * Approach: count each value's frequency in a hash map, then insert the
 * frequencies into a set; they are all unique iff no insertion collides.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> freq;
        for (int x : arr) ++freq[x];
        unordered_set<int> seen;
        for (auto& [value, count] : freq)
            if (!seen.insert(count).second) return false;
        return true;
    }
};
