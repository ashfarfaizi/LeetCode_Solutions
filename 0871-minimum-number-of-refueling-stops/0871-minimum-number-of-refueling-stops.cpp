/*
 * Approach: greedy with a max-heap. Drive as far as the current fuel allows,
 * pushing the fuel of every station passed onto a heap. Whenever we can't
 * reach the next station (or the target), retroactively refuel at the
 * largest station passed so far; if the heap is empty we're stuck. Each pop
 * is one stop, and choosing the biggest tank each time minimises stops.
 *
 * Time:  O(n log n)
 * Space: O(n)
 */
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> passed;
        long long reach = startFuel;
        int stops = 0, i = 0, n = stations.size();
        while (reach < target) {
            while (i < n && stations[i][0] <= reach) passed.push(stations[i++][1]);
            if (passed.empty()) return -1;
            reach += passed.top();
            passed.pop();
            ++stops;
        }
        return stops;
    }
};
