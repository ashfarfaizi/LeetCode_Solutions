/*
 * Approach: Difference array over locations. Add the passenger count at the
 * pickup point and subtract it at the drop-off point, then take a running
 * sum; if the load ever exceeds capacity the trips cannot all be served.
 * Locations are bounded by 1000.
 *
 * Time:  O(n + L) with L = 1001
 * Space: O(L)
 */
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        array<int, 1002> diff{};
        for (const auto& t : trips) {
            diff[t[1]] += t[0];
            diff[t[2]] -= t[0];
        }
        int load = 0;
        for (int d : diff) {
            load += d;
            if (load > capacity) return false;
        }
        return true;
    }
};
