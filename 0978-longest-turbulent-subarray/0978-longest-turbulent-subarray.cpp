/*
 * Approach: track two running lengths ending at index i: up = longest
 * turbulent run whose last step goes up (arr[i-1] < arr[i]) and down = one
 * whose last step goes down. An up step extends a run that last went down,
 * and vice versa; an equal pair resets both to 1.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int up = 1, down = 1, best = 1;
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i - 1] < arr[i]) {
                up = down + 1;
                down = 1;
            } else if (arr[i - 1] > arr[i]) {
                down = up + 1;
                up = 1;
            } else {
                up = down = 1;
            }
            best = max(best, max(up, down));
        }
        return best;
    }
};
