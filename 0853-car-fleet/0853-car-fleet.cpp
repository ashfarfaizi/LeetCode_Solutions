/*
 * Approach: sort cars by position, closest to the target first, and compute
 * each car's arrival time if it drove alone. Scanning from the front, a car
 * that would arrive no later than the fleet ahead of it catches up and
 * joins it; a car that would arrive strictly later starts a new fleet whose
 * arrival time becomes the new bound.
 *
 * Time:  O(n log n)
 * Space: O(n)
 */
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, double>> cars(n);
        for (int i = 0; i < n; ++i)
            cars[i] = {position[i], double(target - position[i]) / speed[i]};
        sort(cars.rbegin(), cars.rend());
        int fleets = 0;
        double slowest = 0;
        for (const auto& [pos, time] : cars) {
            if (time > slowest) {
                ++fleets;
                slowest = time;
            }
        }
        return fleets;
    }
};
