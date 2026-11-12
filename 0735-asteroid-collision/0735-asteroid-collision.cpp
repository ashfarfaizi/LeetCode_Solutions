/*
 * Approach: Stack. Push right-movers; an incoming left-mover destroys smaller
 * right-movers on top of the stack until it is destroyed, ties, or meets
 * nothing moving right.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;
        for (int a : asteroids) {
            bool alive = true;
            while (alive && a < 0 && !st.empty() && st.back() > 0) {
                if (st.back() < -a) {
                    st.pop_back();
                    continue;
                }
                if (st.back() == -a) st.pop_back();
                alive = false;
            }
            if (alive) st.push_back(a);
        }
        return st;
    }
};
