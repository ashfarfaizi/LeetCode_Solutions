/*
 * Approach: BFS where each level is one more bus taken. Map every stop to the
 * routes serving it. From the current stops, board each unused route that
 * serves them and enqueue all of that route's stops. Marking routes as used
 * ensures each route's stop list is scanned only once.
 * Time: O(sum of route lengths), Space: O(sum of route lengths)
 */
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        unordered_map<int, vector<int>> by_stop;
        for (int r = 0; r < (int)routes.size(); ++r)
            for (int stop : routes[r]) by_stop[stop].push_back(r);
        vector<bool> used(routes.size(), false);
        unordered_set<int> seen = {source};
        queue<int> q;
        q.push(source);
        for (int buses = 1; !q.empty(); ++buses) {
            for (int sz = q.size(); sz > 0; --sz) {
                int stop = q.front();
                q.pop();
                for (int r : by_stop[stop]) {
                    if (used[r]) continue;
                    used[r] = true;
                    for (int next : routes[r]) {
                        if (next == target) return buses;
                        if (seen.insert(next).second) q.push(next);
                    }
                }
            }
        }
        return -1;
    }
};
