/*
 * Approach: Greedy - walk the bed and plant in every empty plot whose left and
 * right neighbours (treating the ends as empty) are also empty. Planting as
 * early as possible never reduces how many flowers fit later.
 * Time: O(m), Space: O(1)
 */
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int m = flowerbed.size();
        for (int i = 0; i < m && n > 0; ++i) {
            if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) &&
                (i == m - 1 || flowerbed[i + 1] == 0)) {
                flowerbed[i] = 1;
                --n;
            }
        }
        return n <= 0;
    }
};
