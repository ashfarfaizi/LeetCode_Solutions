/*
 * Approach: Track net displacement. Each move changes x or y by one; the
 * robot is home exactly when both coordinates end at zero.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    bool judgeCircle(string moves) {
        int x = 0, y = 0;
        for (char c : moves) {
            switch (c) {
                case 'U': ++y; break;
                case 'D': --y; break;
                case 'L': --x; break;
                case 'R': ++x; break;
            }
        }
        return x == 0 && y == 0;
    }
};
